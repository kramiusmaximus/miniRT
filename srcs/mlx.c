#include "miniRT.h"

int start_mlx(t_vars *vars)
{
	t_mlx *mlx;
	t_scene *scene;
	t_image image;


	mlx = vars->mlx;
	scene = vars->scene;
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, scene->window_dims.width, scene->window_dims.height, "Is this god?");
	image.img = mlx_new_image(mlx->mlx, scene->window_dims.width, scene->window_dims.width);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian);
	mlx->image = image;
	mlx_loop_hook(mlx->mlx, render_image, &vars);
	//mlx_hook(image.img, 2, 1L<<0, move_camera, &vars);
	mlx_key_hook(mlx->win, move_camera, &vars);
	mlx_loop(mlx->mlx);
}