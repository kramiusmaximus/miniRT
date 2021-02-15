#include <tcl.h>
#include "miniRT.h"

extern 		t_vars vars;

t_intersect *trace_result(t_ray *ray, t_scene *scene, double d)
{
	t_object	*obj;
	t_object	*obj_closest;
	t_t 		t;
	int 		i;

	t.closest = MAX_DIST;
	if (!ray || !scene)
		return (NULL);
	obj = scene->object;
	obj_closest = NULL;
	while (obj)
	{
		t.size = 0;
		if (obj->type & SP)
			ray_intersect_sphere(ray, obj, &t);
		else if (obj->type & PL)
			ray_intersect_plane(ray, obj, &t);
		else if (obj->type & SQ)
			ray_intersect_sq(ray, obj, &t);
		else if (obj->type & CY)
			ray_intersect_cy(ray, obj, &t);
		else if (obj->type & TR)
			ray_intersect_tr(ray, obj, &t);
		i = 0;
		while (i < t.size)
		{
			if (t.arr[i] > d && t.arr[i] < t.closest)
			{
				t.closest = t.arr[i];
				obj_closest = obj;
			}
			i++;
		}
		obj = obj->next;
	}
	if (obj_closest)
		return (ray->intersect = process_t(ray, obj_closest, &t));
	return (NULL);
}

int trace_ray(t_ray *ray, t_scene *scene, int n_passes, double d)
{
	t_intersect int_p;
	double 		closest_t;
	t_intersect *inter;
	int 		color;
	int 		light_effects;
	t_ray 		ref_ray;
	int 		l_color;
	if ((inter = trace_result(ray, scene, d)))
	{
		ref_ray = make_ray(inter->contact, v_normalize(inter->ref_dir));
		color = inter->obj->color;
		l_color = process_light(ray, scene);
		color = rgb_multiply(color, l_color);
		if (--n_passes && inter->obj->reflectivity)
			color = rgb_add(rgb_multiply_scalar(color, 1 - inter->obj->reflectivity), \
		rgb_multiply_scalar(trace_ray(&ref_ray, scene, n_passes, EPS), inter->obj->reflectivity));
		return (color);
	}
	return (BG_COLOR);
}