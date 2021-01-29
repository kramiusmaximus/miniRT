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

int trace_ray(t_vector cam_coords, t_vector c_coords, t_spheres spheres)
{
	double t[] = {MAX_DIST, MAX_DIST};
	int closest_t = MAX_DIST;
	t_sphere *closest_sp = NULL;
	int d = 1; // should this be constant?
	int color = 0;

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
	t_vector c_coords;

	for (int y = 0; y < scene->res.height; y++)
	{
		for (int x = 0; x < scene->res.width; x++)
		{
			// need to process camera rotation as well
			c_coords = canvas_to_coords(x, y, scene);
			color = trace_ray(scene->camera.coordinates, c_coords, scene->spheres);
			put_pixel(&vars->image, x, y, color);
		}
	}
	return (0);
}