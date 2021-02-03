#include <tcl.h>
#include <tclDecls.h>
#include <tclTomMath.h>
#include "miniRT.h"

int main()
{
	// stuff that would come from the parser. Parser would return a 'scene' file I reckon;
	int z = 65;
	t_scene		scene;
	t_ambient	ambient = {0.1, 0x00FFFFFF};
	t_light		l1 = {1, {0,60, z}, 0x00FFFFFF};
	t_lights	lights = {1, {l1}};
	t_camera	camera = {0, {3,0,0, 0}, {0,0, 0}, 60, 1};
	t_sphere	sp1 = {0, 10, {3, 0, 0, z}, 0x00FF0000};
	t_sphere	sp2 = {0, 10, {3, 15, 0, z}, 0x0000FF00};
	t_sphere	sp4 = {0, 10, {3, -15, 0, z}, 0x0000FF00};
	t_sphere	sp3 = {0, 10, {3, 30, 0, z}, 0x000000FF};
	t_sphere	sp5 = {0, 10, {3, -30, 0, z}, 0x000000FF};
	t_spheres	spheres = {5, {sp1, sp2, sp3, sp4, sp5}};
	t_res		res = {600, 600};
	t_vars		vars;
	t_image 	image;

	// initializing scene;
	scene.res = res;
	scene.camera = camera;
	scene.ambient = ambient;
	scene.lights = lights;
	scene.spheres = spheres;

	// lets get the party started;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, res.width, res.height, "Is this god?");
	image.img = mlx_new_image(vars.mlx, res.width, res.height);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian);
	vars.image = image;
	render_image(&vars, &scene);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.image.img, 0, 0);
	mlx_loop(vars.mlx);
}

