#include <tcl.h>
#include <tclDecls.h>
#include <tclTomMath.h>
#include "miniRT.h"

int move_camera(int key, t_vars *vars)
{
	if (key == 13)
	{
		vars->scene->camera->coordinates.z += 2;
	}
	else if (key == 0)
	{
		vars->scene->camera->coordinates.x -= 2;
	}
	else if (key == 1)
	{
		vars->scene->camera->coordinates.z -= 2;
	}
	else if (key == 2)
	{
		vars->scene->camera->coordinates.x += 2;
	}
	else if (key == 3)
	{
		vars->scene->camera->coordinates.y += 2;
	}
	else if (key == 5)
	{
		vars->scene->camera->coordinates.y -= 2;
	}
	printf("%d\n", key);
	return (0);
}

int main()
{
	// stuff that would come from the parser. Parser would return a 'scene' file I reckon;
	int z = 100;
	t_scene		scene;
	t_ambient	ambient = {0.2, 0x00FFFFFF};
	t_light		l1 = {1, {0,10000, z}, 0x00FFFFFF, NULL};
	t_light		l2 = {0, {0,0, 0}, 0x00FFFFFF, &l1};
	t_camera	camera = {{0,0,0}, {0,0, 0}, 70, 1, NULL};
	t_sp		sp1 = {{-20, 0, z }, 30};
	t_sp		sp2 = {{20, 0, z}, 30};
	t_sp		sp3 = {{0, 0, z}, 30};
	t_object	object0 = {SP, sp1,0,0,0x00FF0000, NULL};
	t_object	object1 = {SP, sp2,0,0,0x0000FF00, &object0};
	t_object	object2 = {SP, sp3,0,0,0x000000FF, &object1};
	t_dims		window_dims = {720, 1280};
	t_dims		image_res = {720, 1280};
	t_mlx		mlx;
	t_image 	image;

	// initializing scene;
	scene.window_dims = window_dims;
	scene.res = image_res;
	scene.camera = &camera;
	scene.ambient = ambient;
	scene.light = &l2;
	scene.object = &object2;

	// init t_vars;
	t_vars	vars = {&mlx, &scene};

	// lets get the party started;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, window_dims.width, window_dims.height, "Is this god?");
	image.img = mlx_new_image(mlx.mlx, window_dims.width, window_dims.width);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian);
	mlx.image = image;
	mlx_loop_hook(vars.mlx->mlx, render_image, &vars);
	//mlx_hook(image.img, 2, 1L<<0, move_camera, &vars);
	mlx_key_hook(vars.mlx->win, move_camera, &vars);
	mlx_loop(vars.mlx->mlx);
}

