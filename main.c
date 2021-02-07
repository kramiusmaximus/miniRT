#include "miniRT.h"
#include <pthread.h>

t_vars	vars;
int		**prev_frame;


int	initiate_jesus_resurrection()
{
	// stuff that would come from the parser. Parser would return a 'scene' file I reckon;
	int z = 	300;
	t_scene		scene;
	t_ambient	ambient = {0.2 , 0x00FFFFFF};
	t_light		l1 = {1, {600,300, z - 150}, 0x00FFFFFF, NULL};
	//t_light		l2 = {0, {0,0, 0}, 0x00FFFFFF, &l1};
	t_camera	camera = {{0,0,0}, {0,0, 0}, 70, 1, NULL};
	t_sp		sp1 = {{-70, 0, z }, 30};
	t_sp		sp2 = {{0, 0, z}, 100};
	t_sp		sp3 = {{70, 0, z}, 30};
	t_sp		sp4 = {{20, 20, z-55}, 20};
	t_object	object0 = {SP, sp1,0,0,0x00FF0000, NULL};
	t_object	object1 = {SP, sp2,0,0.5,0x0000FF00, &object0};
	t_object	object2 = {SP, sp3,0,0,0x000000FF, &object1};
	t_object	object3 = {SP, sp4,0,0,0x00FF00FF, &object2};

	t_dims		window_dims = {720, 1280};
	t_dims		image_res = {720, 1280};
	t_mlx		mlx;
	t_image 	image;

	vars.mlx = &mlx;
	vars.scene = &scene;

	// initializing scene;  use parser for this
	scene.window_dims = window_dims;
	scene.res = image_res;
	scene.camera = &camera;
	scene.ambient = ambient;
	scene.light = &l1;
	scene.object = &object3;

	prev_frame = malloc(sizeof(int) * scene.window_dims.width * scene.window_dims.height);
	// lets get the party started;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, window_dims.width, window_dims.height, "Is this god?");
	image.img = mlx_new_image(mlx.mlx, window_dims.width, window_dims.width);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian);
	mlx.image = image;
	mlx_loop_hook(vars.mlx->mlx, render_image, &vars);
	mlx_key_hook(vars.mlx->win, move_camera, &vars);
	mlx_loop(vars.mlx->mlx);
}

int main()
{
	initiate_jesus_resurrection();
	return (0);
}

