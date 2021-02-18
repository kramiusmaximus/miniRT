#include <tcl.h>
#include "miniRT.h"


t_intersect *trace_result(t_ray *ray, t_scene *scene, double d)
{
	t_list 		*p;
	t_object	*obj;
	t_object	*obj_closest;
	t_t 		t;
	int 		i;

	t.closest = MAX_DIST;
	if (!ray || !scene)
		return (NULL);
	p = scene->object;
	obj_closest = NULL;
	while (p)
	{
		obj = p->content;
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
		p = p->next;
	}
	if (obj_closest)
		return (ray->intersect = process_t(ray, obj_closest, &t));
	return (NULL);
}

int trace_ray(t_ray *ray, t_scene *scene, int n_passes, double d)
{
	t_intersect *inter;
	int 		c[3] = {0,0,0};
	t_ray 		ref_ray;

	if ((inter = trace_result(ray, scene, d)))
	{
		ref_ray = make_ray(inter->contact, v_normalize(inter->ref_dir));
		c[0] = inter->obj->color;
		process_light(ray, scene, c);
		c[1] = rgb_multiply(c[0], c[1]);
		//c[2] = rgb_multiply(c[0], c[2]);
		c[0] = rgb_add(c[1], c[2]);
		if (--n_passes && inter->obj->reflectivity)
			c[0] = rgb_add(rgb_multiply_scalar(c[0], 1 - inter->obj->reflectivity), rgb_multiply_scalar(trace_ray(&ref_ray, scene, n_passes, EPS), inter->obj->reflectivity));
		free(inter);
	   	return (c[0]);
	}
	return (BG_COLOR);
}