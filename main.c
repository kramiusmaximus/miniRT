#include "miniRT.h"
#include <pthread.h>

/*
int	initiate_jesus_resurrection()
{
	// stuff that would come from the parser. Parser would return a 'scene' file I reckon;
	int z = 	300;
	t_ambient	ambient = {0.1 , 0x00FFFFFF};
	t_vars		vars;
	t_light		l1 = {0.3, {-300,200, z}, 0x00FF0505, NULL};
	t_light		l2 = {0.3, {300,200, z}, 0x000505FF, &l1};
	t_light		l3 = {0.6, {0,200, 20}, 0x00FFFFFF, &l2};

	// shapes
	t_camera	camera0 = {{0, 50, 0}, {0, 0, 0}, 90, 1, NULL};
	t_camera	camera1 = {{0, 20, 0}, {0, 0, 0}, 90, 1, &camera0};
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
	t_object	object0 = {SP, (t_shape)&sp0, {-40, -65, z - 10 }, 0, 0.6, 0x006FFF7E, NULL};
	t_object	object1 = {SP, (t_shape)&sp1, {0, 0, z},0, 0.6, 0x00FFFFFF , &object0};
	t_object	object2 = {SP, (t_shape)&sp2,{70, 0, z}, 0, 0.6, 0x006FFFFD, &object1};
	t_object	object3 = {SP, (t_shape)&sp3, {20, 20, z - 55},0, 0.6, 0x007E6FFF, &object2};
	t_object	object4 = {PL, (t_shape)&pl0, {0, -150, 0},0, 0.08, 0x00A9FFD5, &object3};
	t_object	object5 = {SQ, (t_shape)&sq0,{0, -50, z}, 0, 0.6, 0x00FF8EE1, &object4};
	t_object	object6 = {CY, (t_shape)&cy0, {0, -50, z - 50},0.00, 1, 0x007A9FFF, &object5};
	t_object	object7= {TR, (t_shape)&tr0, {0,0,0},0, 0.6, 0x00FFD064, &object6};
	t_object	object8 = {SP, (t_shape)&sp3, {0, 60, z },0, 0.6, 0x007E6FFF, &object7};
	vars.mlx.window_dims.width  = 720;
	vars.mlx.window_dims.height = 1280;
	vars.scene.res.width = 1280;
	vars.scene.res.height = 720;
	vars.nav.fwd_back = 0;
	vars.nav.lft_rght = 0;
	vars.nav.up_dwn = 0;
	vars.rendered = 0;
	vars.scene.adjustment_factor = 1;
	vars.scene.parked = 0;
	vars.scene.camera = &camera1;
	vars.scene.ambient = ambient;
	vars.scene.light = &l3;
	vars.scene.object = &object8;

	// lets get the party started;
	vars.mlx.mlx = mlx_init();
	vars.mlx.win = mlx_new_window(vars.mlx.mlx, vars.mlx.window_dims.width, vars.mlx.window_dims.height, "Is this god?");
	vars.mlx.image.img = mlx_new_image(vars.mlx.mlx, vars.mlx.window_dims.width, vars.mlx.window_dims.height);
	vars.mlx.image.addr = mlx_get_data_addr(vars.mlx.image.img, &vars.mlx.image.bits_per_pixel, &vars.mlx.image.line_length, &vars.mlx.image.endian);
	mlx_loop_hook(vars.mlx.mlx, render, &vars);
	mlx_hook(vars.mlx.win, 2, 1L << 2, key_press_hook, &vars);
	mlx_hook(vars.mlx.win, 3, 1L << 3, key_release_hook, &vars);
	mlx_hook(vars.mlx.win, 17, 1L << 17, exit_hook, &vars);
	mlx_loop(vars.mlx.mlx);
}
 */

int error(char *msg)
{
	perror(msg);
	exit(errno);
}



int make_bmp(char *rt)
{}

int launch_renderer(char *rt)
{
	t_vars	vars;

	parse_rt(rt, &vars.scene);  /// process errors
	// lets get the party started;
	vars.rendered = 0;
	vars.nav.up_dwn = 0;
	vars.nav.lft_rght = 0;
	vars.nav.fwd_back = 0;
	vars.mlx.mlx = mlx_init();
	vars.mlx.window_dims.height = 720;
	vars.mlx.window_dims.width = 1280;
	if (vars.mlx.window_dims.height < vars.scene.res.height ||  /// should use res parameter rather than windwo_dims in vars. Also make more pretty
		vars.mlx.window_dims.width < vars.scene.res.width)
	{
		vars.scene.res.height = vars.mlx.window_dims.height;
		vars.scene.res.width = vars.mlx.window_dims.width;
	}
	vars.mlx.win = mlx_new_window(vars.mlx.mlx, vars.mlx.window_dims.width, vars.mlx.window_dims.height, "Is this god?");
	vars.mlx.image.img = mlx_new_image(vars.mlx.mlx, vars.mlx.window_dims.width, vars.mlx.window_dims.width);
	vars.mlx.image.addr = mlx_get_data_addr(vars.mlx.image.img, &vars.mlx.image.bits_per_pixel, &vars.mlx.image.line_length, &vars.mlx.image.endian);
	mlx_loop_hook(vars.mlx.mlx, render, &vars);
	mlx_hook(vars.mlx.win, 2, 1L << 2, key_press_hook, &vars);
	mlx_hook(vars.mlx.win, 3, 1L << 3, key_release_hook, &vars);
	mlx_hook(vars.mlx.win, 17, 1L << 17, exit_hook, &vars);
	mlx_loop(vars.mlx.mlx);
	printf("hey");
}




int main(int n_args, char **args)
{
	if (n_args == 3)
	{
		if (!ft_strcmp(args[2], "--save"))
			make_bmp(args[1]);
		else
			ft_printf("Incorrect argument (%s) specified. Use '--save' as second argument to save scene as .bmp file.\n", args[2]);
	}  // access given rt file, render it into a bmp file format, save it in 'rendered files' folder
	if (n_args == 2)
		launch_renderer(args[1]); // open window, access given rt file, and render it, and upload it to the opened window
	/// initiate_jesus_resurrection();
	return (0);
}

