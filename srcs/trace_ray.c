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
		{}
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



int 		trace_ray(t_ray	*ray, t_scene *scene)
{
	t_intersect int_p;
	double 		closest_t;
	t_intersect *inter;
	int 		color;
	int 		light_effects;

	if ((inter = trace_result(ray, scene, 1)))
	{
		color = inter->obj->color;
		light_effects = process_light(ray, scene);
		//origin = v_add(origin, v_scalar_mult(dir, closest_t));
		//dir = surface_vector(inter, origin);
		return (rgb_multiply(color, light_effects));
		//return (rgb_add(rgb_multiply_scalar(color, (1 - inter->reflectivity)),rgb_multiply_scalar(, )));
	}
	return (0xE9DC65);
}