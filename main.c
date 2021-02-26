#include "miniRT.h"

int error(char *msg, t_scene *scene)
{
	t_object *obj;
	t_camera *cam;
	ft_lstclear(&scene->object, ft_lstdelone);
	// ft_lstclear(&scene->camera, ft_lstdelone) ///need to clear cams
	if (msg)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(msg, 2);
		ft_putchar_fd('\n', 2);
		exit(228);
	}
	perror(NULL);
	exit(errno);
}

int start_mlx_process(t_vars *vars)
{
	mlx_loop_hook(vars->mlx.mlx, render_mlx, vars);
	mlx_hook(vars->mlx.win, 2, 1L << 2, key_press_hook, vars);
	mlx_hook(vars->mlx.win, 3, 1L << 3, key_release_hook, vars);
	mlx_hook(vars->mlx.win, 17, 1L << 17, exit_hook, vars);
	mlx_loop(vars->mlx.mlx);
}


int init_vars(char *rt, t_vars *vars, int bmp)
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
		vars->mlx.win = mlx_new_window(vars->mlx.mlx, vars->mlx.window_dims.width, vars->mlx.window_dims.height,
									   "Is this god?");
		vars->mlx.image.img = mlx_new_image(vars->mlx.mlx, vars->mlx.window_dims.width, vars->mlx.window_dims.width);
		vars->mlx.image.addr = mlx_get_data_addr(vars->mlx.image.img, &vars->mlx.image.bits_per_pixel,
												 &vars->mlx.image.line_length, &vars->mlx.image.endian);
	}
}

int launch_renderer(char *rt, int bmp)
{
	t_vars	vars;

	init_vars(rt, &vars, bmp);
	if (bmp)
		create_bmp_image(&vars, "../bmp_image");
	else
		start_mlx_process(&vars);
}

int main(int n_args, char **args)
{
	// need to free split in parser
	if (n_args == 3)
	{
		if (!ft_strcmp(args[2], "--save"))
			launch_renderer(args[1], 1);
		else
			ft_printf("Incorrect argument (%s) specified. Use '--save' as second argument to save scene as .bmp file.\n", args[2]);
	}  // access given rt file, render_mlx it into a bmp file format, save it in 'rendered files' folder
	if (n_args == 2)
		launch_renderer(args[1], 0); // open window, access given rt file, and render_mlx it, and upload it to the opened window
	return (0);
}
