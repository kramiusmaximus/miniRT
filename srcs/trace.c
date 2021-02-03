#include "miniRT.h"

t_object	*ray_intersect_sphere(t_3dvec cam_coords, t_3dvec c_coords, t_object *sphere_obj, double *t)
{
	double k1 = vector_dot(vector_subtract(c_coords, cam_coords),vector_subtract(c_coords, cam_coords));
	double k2 = 2 * vector_dot(vector_subtract(cam_coords, sphere_obj->shape.sp.coordinates), vector_subtract(c_coords, cam_coords));
	double k3 = vector_dot(vector_subtract(cam_coords, sphere_obj->shape.sp.coordinates), vector_subtract(cam_coords, sphere_obj->shape.sp.coordinates)) - pow(sphere_obj->shape.sp.diameter / 2, 2);
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
		return (NULL);
	}
	return (sphere_obj);
}

t_object *trace_result(t_3dvec cam_coords, t_3dvec c_coords, double *closest_t, t_scene *scene)
{
	t_object	*object_hit_closest;
	t_object	*object_hit;
	double 		t[] = {MAX_DIST, MAX_DIST};
	t_object	*p;

	object_hit_closest = NULL;
	if (!closest_t || !scene)
		return (NULL);
	p = scene->object;
	while (p)
	{
		if (p->type & SP)
			object_hit = ray_intersect_sphere(cam_coords, c_coords, p, &t);
		else if (p->type & PL)
		{}
		else if (p->type & SQ)
		{}
		else if (p->type & CY)
		{}
		else if (p->type & TR)
		{}
		if (t[0] > 1 && t[0] < *closest_t)
		{
			*closest_t = t[0];
			object_hit_closest = object_hit;
		}
		else if (t[1] > 1 && t[1] < *closest_t)
		{
			*closest_t = t[1];
			object_hit_closest = object_hit;
		}
		p = p->next;
	}
	return (object_hit_closest);
}

int trace_ray(t_3dvec cam_coords, t_3dvec c_coords, t_scene	*scene)
{
	double		closest_t;
	t_object	*closest_obj;
	int			color;

	closest_t = MAX_DIST;
	color = 0;
	if ((closest_obj = trace_result(cam_coords, c_coords, &closest_t, scene)))
	{
		color = closest_obj->color;
	}
	return (color);
}

int render_image(t_vars *vars, t_scene *scene)
{
	int color;
	double x_mult;
	double y_mult;
	t_3dvec c_coords;

	if (!vars || !scene)
		return (-1);
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
					color = trace_ray(scene->camera->coordinates, c_coords, scene);
					put_pixel(&vars->image, x, y, color);
				}
			}
		}
	}
	return (0);
}