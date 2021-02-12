#include "miniRT.h"
#include <pthread.h>

t_vars	vars;

int	initiate_jesus_resurrection()
{
	// stuff that would come from the parser. Parser would return a 'scene' file I reckon;
	int z = 	300;
	t_scene		scene;
	t_ambient	ambient = {0.3 , 0xE9DC65};
	t_light		l1 = {0.7, {300,300, z - 100}, 0x00FFFFFF, NULL};
	//t_light		l2 = {0, {0,0, 0}, 0x00FFFFFF, &l1};

	// shapes
	t_camera	camera = {{0,0,0}, {0,0, 0}, 90, 1, NULL};
	t_sp		sp1 = {{-70, 0, z - 20 }, 30};
	t_sp		sp2 = {{0, 0, z}, 100};
	t_sp		sp3 = {{70, 0, z}, 30};
	t_sp		sp4 = {{20, 20, z-55}, 20};
	t_pl		pl1 = {{0, -60, 0}, {0,1,0}};
	t_sq		sq1 = {{0, -50, z}, {0,1,0}, {0,0,1}, {1,0,0}, 120};
	t_cy		cy1 = {{30,-50,z - 45}, {0, 1, 0}, 15, 25};
	// ^ need to figure out how to find front and side vectors, and rotation of shapes in general...


	// objects
	t_object	object0 = {SP, (t_shape)sp1,0,0,0x006FFF7E, NULL};
	t_object	object1 = {SP, (t_shape)sp2,0,0.5,0x00FFA267 , &object0};
	t_object	object2 = {SP, (t_shape)sp3,0,0,0x006FFFFD, &object1};
	t_object	object3 = {SP, (t_shape)sp4,0,0,0x007E6FFF, &object2};
	t_object	object4 = {PL, (t_shape)pl1,0,0,0x00A9FFD5, &object3};
	t_object	object5 = {SQ, (t_shape)sq1,0,0,0x00FF8EE1, &object4};
	t_object	object6 = {CY, (t_shape)cy1,0,0,0x007A9FFF, &object5};
	t_dims		window_dims = {720, 1280};
	t_dims		image_res = {720, 1280};
	t_mlx		mlx;
	t_image 	image;

	t_nav		nav = {0,0,0};

	vars.mlx = &mlx;
	vars.scene = &scene;
	vars.nav = nav;

	// initializing scene;  use parser for this
	scene.window_dims = window_dims;
	scene.res = image_res;
	scene.adjustment_factor = 1;
	scene.parked = 0;
	scene.camera = &camera;
	scene.ambient = ambient;
	scene.light = &l1;
	scene.object = &object6;

	// lets get the party started;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, window_dims.width, window_dims.height, "Is this god?");
	image.img = mlx_new_image(mlx.mlx, window_dims.width, window_dims.width);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian);
	mlx.image = image;
	mlx_loop_hook(vars.mlx->mlx, render_image, &vars);
	mlx_hook(vars.mlx->win, 2, 1L << 2, button_press, &vars);
	mlx_hook(vars.mlx->win, 3, 1L << 3, button_release, &vars);
	//mlx_key_hook(vars.mlx->win, move_camera, &vars);
	mlx_loop(vars.mlx->mlx);
}

int main()
{
	initiate_jesus_resurrection();
	return (0);
}

