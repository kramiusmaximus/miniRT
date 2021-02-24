#include "miniRT.h"

int error(char *msg, t_scene *scene)
{
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

/*
int make_bmp(char *rt)
{
	if (bmp)
	{
		bmpim->header.type = 0x4d42;
		bmpim->header.offset = 54;
		bmpim->header.dib_header_size = 40;
		bmpim->header.bits_per_pixel = 32;
		bmpim->header.width_px = vars->scene.res.width;
		bmpim->header.height_px = vars->scene.res.height;
		bmpim->header.image_size_bytes = bmpim->header.bits_per_pixel * bmpim->header.width_px * bmpim->header.height_px / 8;
		bmpim->header.size = bmpim->header.dib_header_size + bmpim->header.image_size_bytes;
		bmpim->header.num_colors = 3;
	}
}
*/

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
	t_BMPImage *bmpim;

	bmpim = &vars->bmpim;
	ft_bzero(vars, sizeof(t_vars));
	parse_rt(rt, &vars->scene);
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
	else
		vars->bmpim.image = malloc(sizeof(unsigned int) * vars->scene.res.height * vars->scene.res.width);  /// will need to free
}

int launch_renderer(char *rt, int bmp)
{
	t_vars	vars;

	init_vars(rt, &vars, 0);
	if (bmp)
		make_bmp(&vars);
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
	}  // access given rt file, render_mlx it into a bmp file format, save it in 'rendered files' folder
	if (n_args == 2)
		launch_renderer(args[1], 0); // open window, access given rt file, and render_mlx it, and upload it to the opened window
	return (0);
}
