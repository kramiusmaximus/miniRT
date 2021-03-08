#include "minirt.h"

void start_mlx_process(t_vars *vars)
{
	mlx_loop_hook(vars->mlx.mlx, render_mlx, vars);
	mlx_hook(vars->mlx.win, 2, 1L << 2, (int (*)()) key_press_hook1, vars);
	mlx_hook(vars->mlx.win, 3, 1L << 3, (int (*)())key_release_hook, vars);
	mlx_hook(vars->mlx.win, 17, 1L << 17, exit_hook, vars);
	mlx_loop(vars->mlx.mlx);
}

void init_vars(char *rt, t_vars *vars, int bmp)
{
	ft_bzero(vars, sizeof(t_vars));
	parse_rt(rt, &vars->scene);
	vars->af = 1;
	if (!bmp)
	{
		vars->mlx.mlx = mlx_init();
		vars->mlx.window_dims.height = WINDOW_HEIGHT;
		vars->mlx.window_dims.width = WINDOW_WIDTH;
		if (vars->mlx.window_dims.height < vars->scene.res.height ||
			vars->mlx.window_dims.width < vars->scene.res.width)
		{
			vars->scene.res.height = vars->mlx.window_dims.height;
			vars->scene.res.width = vars->mlx.window_dims.width;
		}
		vars->mlx.win = mlx_new_window(vars->mlx.mlx, vars->scene.res.width, vars->scene.res.height,
									   "Is this god?");
		vars->mlx.image.img = mlx_new_image(vars->mlx.mlx, vars->scene.res.width, vars->scene.res.height);
		vars->mlx.image.addr = mlx_get_data_addr(vars->mlx.image.img, &vars->mlx.image.bits_per_pixel,
												 &vars->mlx.image.line_length, &vars->mlx.image.endian);
	}
}

void launch_renderer(char *rt, int bmp)
{
	t_vars	vars;

	init_vars(rt, &vars, bmp);
	if (bmp)
		create_bmp_image(&vars, "../bmp_image.bmp");
	else
		start_mlx_process(&vars);
}

int main(int n_args, char **args)
{
	if (n_args == 3)
	{
		if (!ft_strcmp(args[2], "--save"))
			launch_renderer(args[1], 1);
		else
			ft_printf("Incorrect argument (%s) specified. Use '--save' as second argument to save scene as .bmp file.\n", args[2]);
	}
	if (n_args == 2)
		launch_renderer(args[1], 0);
	return (0);
}
