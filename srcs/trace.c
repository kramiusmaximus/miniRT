#include "miniRT.h"

void ray_intersect_sphere(t_vector cam_coords, t_vector c_coords, t_sphere sphere, double t[2])
{
	double k1 = vector_dot(vector_subtract(c_coords, cam_coords),vector_subtract(c_coords, cam_coords));
	double k2 = 2 * vector_dot(vector_subtract(cam_coords, sphere.coordinates), vector_subtract(c_coords, cam_coords));
	double k3 = vector_dot(vector_subtract(cam_coords, sphere.coordinates), vector_subtract(cam_coords, sphere.coordinates)) - pow(sphere.diameter / 2, 2);
	double discriminant = pow(k2, 2) - 4 * k1 * k3;

	if (pow(discriminant, 3) < 1 && pow(discriminant, 3) > -1) // 1 solution
	{
		t[0] = -k2 / (2 * k1);
		t[1] = MAX_DIST;
	}
	else if (discriminant > 0)				// 2 solutions
	{
		t[0] = -k2 / (2 * k1) + sqrt(discriminant);
		t[1] = -k2 / (2 * k1) - sqrt(discriminant);
	}
	else
	{
		t[0] = MAX_DIST;
		t[1] = MAX_DIST;
	}
}

int cast_ray(t_vector cam_coords, t_vector c_coords, t_spheres spheres)
{
	double t[] = {MAX_DIST, MAX_DIST};
	int closest_t = MAX_DIST;
	t_sphere *closest_sp = NULL;
	int d = 1; // should this be constant?
	int color = 0;

	if (trace())

	for (int i = 0; i < spheres.count; i++)		// can optimize by sorting list of objects by distance from camera
	{
		ray_intersect_sphere(cam_coords, c_coords, spheres.arr[i], t);
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
	{
		color = closest_sp->color;
	}
	return (color);
}

int render_image(t_vars *vars, t_scene *scene)
{
	int color;
	double x_mult;
	double y_mult;
	t_vector c_coords;

	y_mult = ((double)scene->window_dims.height / (double)scene->res.height);
	x_mult = ((double)scene->window_dims.width / (double)scene->res.width);
	for (int y_box = 0; y_box < scene->res.height; y_box++)
	{
		for (int x_box = 0; x_box < scene->res.width; x_box++)
		{
			for (int y = (int)(y_box * y_mult); y < (y_box + 1) * y_mult; y++)
			{
				for (int x = (int)(x_box * x_mult); x < (x_box + 1) * x_mult; x++)
				{
					c_coords = canvas_to_coords(x_box + 0.5, y_box + 0.5, scene);
					color = cast_ray(scene->camera.coordinates, c_coords, scene->spheres);
					put_pixel(&vars->image, x, y, color);
				}
			}
		}
	}
	return (0);
}