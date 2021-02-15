#include "miniRT.h"
#include <pthread.h>

t_vars	vars;

int	initiate_jesus_resurrection()
{
	// stuff that would come from the parser. Parser would return a 'scene' file I reckon;
	int z = 	300;
	t_scene		scene;
	t_ambient	ambient = {0.1 , 0x00FFFFFF};
	t_light		l1 = {0.3, {-300,200, z}, 0x00FF0505, NULL};
	t_light		l2 = {0.3, {300,200, z}, 0x000505FF, &l1};
	t_light		l3 = {0.6, {0,200, 20}, 0x00FFFFFF, &l2};


	// shapes
	t_camera	camera = {{0,50,0}, {0,-0.05, 0}, 90, 1, NULL};
	t_sp		sp0 = {30};
	t_sp		sp1 = { 100};
	t_sp		sp2 = { 30};
	t_sp		sp3 = { 20};
	t_pl		pl0 = { {0, 1, 0}};
	t_sq		sq0 = { {0, 1, 0}, {0, 0, 1}, {1, 0, 0}, 120};
	t_cy		cy0 = { {0.0, 1, .0}, 10, 10};
	t_tr 		tr0 = { { {-100, 0, z},{0,100,z},{100, 0,z}}};
	// ^ need to figure out how to find front and side vectors, and rotation of shapes in general...


	// objects
	t_object	object0 = {SP, (t_shape)&sp0, {-40, -65, z - 10 }, 0, 0.09, 0x006FFF7E, NULL};
	t_object	object1 = {SP, (t_shape)&sp1, {0, 0, z},0, 0.06, 0x00FFFFFF , &object0};
	t_object	object2 = {SP, (t_shape)&sp2,{70, 0, z}, 0, 0.09, 0x006FFFFD, &object1};
	t_object	object3 = {SP, (t_shape)&sp3, {20, 20, z - 55},0, 0.08, 0x007E6FFF, &object2};
	t_object	object4 = {PL, (t_shape)&pl0, {0, -150, 0},0, 0, 0x00A9FFD5, &object3};
	t_object	object5 = {SQ, (t_shape)&sq0,{0, -50, z}, 0, 0.05, 0x00FF8EE1, &object4};
	t_object	object6 = {CY, (t_shape)&cy0, {0, -50, z - 50},0.00, 0.05, 0x007A9FFF, &object5};
	t_object	object7= {TR, (t_shape)&tr0, {0,0,0},0, 0.9, 0x00FFD064, &object6};
	t_object	object8 = {SP, (t_shape)&sp3, {0, 60, z },0, 0.08, 0x007E6FFF, &object7};
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
	scene.light = &l3;
	scene.object = &object8;

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

