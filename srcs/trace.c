#include "miniRT.h"

t_object	*ray_intersect_sphere(t_3dvec p_origin, t_3dvec v_dir, t_object *sphere_obj, double *t)
{
	double a;
	double b;
	double c;
	int solution_n;

	a = vector_dot(v_dir, v_dir);
	b = 2 * vector_dot(vector_subtract(p_origin, sphere_obj->shape.sp.coordinates), v_dir);
	c = vector_dot(vector_subtract(p_origin, sphere_obj->shape.sp.coordinates),vector_subtract(p_origin, sphere_obj->shape.sp.coordinates)) - pow(sphere_obj->shape.sp.diameter / 2, 2);
	solution_n = solve_quadratic(a, b, c, t);
	if (solution_n)
		return (sphere_obj);
	return (NULL);
}
t_3dvec surface_vector(t_object *obj, t_3dvec p_contact)
{
	t_3dvec n = {0,0,0};

	if (obj->type & SP)
	{
		n = vector_normalize(vector_subtract(p_contact, obj->shape.sp.coordinates));
	}
	else if (obj->type & PL)
	{}
	else if (obj->type & SQ)
	{}
	else if (obj->type & CY)
	{}
	else if (obj->type & TR)
	{}
	return (n);
}

t_object *trace_result(t_3dvec p_origin, t_3dvec v_dir, double *closest_t, t_scene *scene, double d)
{
	t_object	*object_hit_closest;
	t_object	*object_hit;
	double 		t[] = {*closest_t, *closest_t};
	t_object	*p;

	object_hit_closest = NULL;
	if (!closest_t || !scene)
		return (NULL);
	p = scene->object;
	while (p)
	{
		if (p->type & SP)
			object_hit = ray_intersect_sphere(p_origin, v_dir, p, &t);
		else if (p->type & PL)
		{}
		else if (p->type & SQ)
		{}
		else if (p->type & CY)
		{}
		else if (p->type & TR)
		{}
		if (t[0] > d && t[0] < *closest_t)
		{
			*closest_t = t[0];
			object_hit_closest = object_hit;
		}
		if (t[1] > d && t[1] < *closest_t)
		{
			*closest_t = t[1];
			object_hit_closest = object_hit;
		}
		p = p->next;
	}
	return (object_hit_closest);
}

int process_light(t_object *obj, t_3dvec contact_p, t_scene *scene)
{
	int light_effects;
	t_3dvec l;
	t_3dvec n;
	double t;
	t_light *p;
	double dot;

	light_effects = rgb_multiply_scalar(scene->ambient.color, scene->ambient.intensity);
	p = scene->light;
	n = surface_vector(obj, contact_p);
	while (p)
	{
		t = 1;
		l = vector_normalize(vector_subtract(p->coordinates, contact_p));
		if (!trace_result(contact_p, vector_subtract(p->coordinates, contact_p), &t, scene, 0.000000000001))
		{
			dot = vector_dot(n, l);
			dot = dot < 0 ? 0 : dot;
			light_effects = rgb_add(light_effects,rgb_multiply_scalar(p->color, dot * p->intensity));
		}
		p = p->next;
	}
	return (light_effects);
}

int trace_ray(t_3dvec cam_coords, t_3dvec v, t_scene	*scene)
{
	double		closest_t;
	t_object	*closest_obj;
	int			color;
	int 		light_effects;

	closest_t = MAX_DIST;
	color = 0;

	for (int i = 0; i < 2; i++)
	{
		if ((closest_obj = trace_result(cam_coords, v, &closest_t, scene, 1)))
		{
			color = closest_obj->color;
			light_effects = process_light(closest_obj, vector_add(cam_coords, vector_scalar_mult(v,closest_t)),scene);
			color = rgb_multiply(color, light_effects);
		}
	}

	return (color);
}

int render_image(t_vars *vars)
{
	t_scene	*scene = vars->scene;
	t_mlx	*mlx = vars->mlx;
	t_camera	*cam = scene->camera;

	int color;
	double x_mult;
	double y_mult;
	t_3dvec c_coords;
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
					color = trace_ray(cam->coordinates, vector_subtract(c_coords, cam->coordinates), scene);
					put_pixel(&mlx->image, x, y, color);
				}
			}
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->image.img, 0, 0);
	return (0);
}