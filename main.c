#include <tcl.h>
#include <tclDecls.h>
#include <tclTomMath.h>
#include "miniRT.h"

int main()
{
	// stuff that would come from the parser. Parser would return a 'scene' file I reckon;
	int z = 90;
	t_scene		scene;
	t_ambient	ambient = {0.1, 0x00FFFFFF};
	t_light		l1 = {1, {0,60, z}, 0x00FFFFFF, NULL};
	t_camera	camera = {{0,0,0}, {0,0, 0}, 70, 1, NULL};
	t_sp		sp1 = {{0, 0, z}, 20};
	t_sp		sp2 = {{20, 20, z}, 20};
	t_sp		sp3 = {{-20, -20, z}, 20};
	t_object	object0 = {SP, sp1,0,0,0x00FF0000, NULL};
	t_object	object1 = {SP, sp2,0,0,0x0000FF00, &object0};
	t_object	object2 = {SP, sp3,0,0,0x000000FF, &object1};
	t_dims		window_dims = {720, 1280};
	t_dims		image_res = {720, 1200};
	t_vars		vars;
	t_image 	image;

	// initializing scene;
	scene.window_dims = window_dims;
	scene.res = image_res;
	scene.camera = &camera;
	scene.ambient = ambient;
	scene.light = &l1;
	scene.object = &object2;

	// lets get the party started;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, window_dims.width, window_dims.height, "Is this god?");
	image.img = mlx_new_image(vars.mlx, window_dims.width, window_dims.width);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian);
	vars.image = image;
	render_image(&vars, &scene);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.image.img, 0, 0);
	mlx_loop(vars.mlx);
}

