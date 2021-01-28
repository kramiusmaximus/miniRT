#include "miniRT.h"

void ray_intersect_sphere(t_vector cam_coords, t_vector c_coords, t_sphere sphere, int *t)
{

}

int trace_ray(t_vector cam_coords, t_vector c_coords, t_spheres spheres)
{
	int t[] = {MAX_DIST, MAX_DIST};
	int closest_t = MAX_DIST;
	t_sphere *closest_sp = NULL;
	int d = cam_coords.z; // should this be constant?
	int color = 0;

	for (int i = 0; i < spheres.count; i++)		// can optimize by sorting list of objects by distance from camera
	{
		ray_intersect_sphere(cam_coords, c_coords, spheres.arr[i], &t);
		if (t[0] > d && t[0] < MAX_DIST && t[0] < closest_t)
		{
			closest_t = t[0];
			closest_sp = &spheres.arr[i];
		}
		if (t[1] > d && t[1] < MAX_DIST && t[1] < closest_t)
		{
			closest_t = t[1];
			closest_sp = &spheres.arr[i];
		}
	}
	if (closest_sp)
		color = closest_sp->color;
	return (color);
}

int render_spheres(t_vars *vars, t_camera camera, t_spheres spheres, t_res res)
{
	int color;
	t_vector c_coords;

	for (int y = 0; y < res.height; y++)
	{
		for (int x = 0; x < res.width; x++)
		{
			// need to process camera rotation as well
			c_coords.y = y;
			c_coords.x = x;
			c_coords.z = res.width / 2 / tan(camera.fov / 2); // may be unnecessary
			color = trace_ray(camera.coordinates, c_coords, spheres);
			put_pixel(vars->image.img, x, y, color);
		}
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->image.img, 0, 0);
	return (0);
}

int main()
{
	t_camera	camera = {0, {0,0,0}, {0,0,}};
	t_sphere	sp1 = {0, 20, {0, 0, 100}, 0x00FF0000};
	t_spheres	spheres = {1, {sp1, 0}};
	t_res		res = {1080, 1920};
	t_vars		vars;
	t_image 	image;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, res.width, res.height, "Is this god?");
	image.img = mlx_new_image(vars.mlx, res.width, res.height);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian);
	vars.image = image;
	render_spheres(&vars, camera, spheres, res);
	mlx_loop(vars.mlx);
}

