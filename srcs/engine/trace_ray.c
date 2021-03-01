#include <tcl.h>
#include "miniRT.h"


t_intersect *trace_result(t_ray *ray, t_scene *scene, double min_d, double max_d)
{
	t_list 		*p;
	t_object	*obj;
	t_object	*obj_closest;
	t_t 		t;
	int 		i;

	t.closest = max_d;
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
			if (t.arr[i] > min_d && t.arr[i] < t.closest)
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

int trace_ray(t_ray *ray, t_scene *scene, int n_passes, double d_min, double d_max)  // add max_d
{
	t_intersect *inter;
	int 		c;
	t_ray 		ref_ray;
	t_ray 		tra_ray;
	double 		dist;
	double 		ref_coeff;

	if ((inter = trace_result(ray, scene, d_min, d_max)))
	{
		c = inter->obj->color;

		// adding transparency
		if (inter->obj->type & (SP | CY))
			tra_ray = make_ray(inter->contact, v_normalize(inter->tra_dir), ray->inside ^ 0b1);
		else
			tra_ray = make_ray(inter->contact, v_normalize(inter->tra_dir), ray->inside);

		if (n_passes > 1 && ray->inside)
			return (trace_ray(&tra_ray, scene, n_passes - 1, EPS, MAX_DIST));
		if (n_passes > 1 && inter->obj->transperancy)
				c = rgb_add_weighted(c, rgb_multiply(c, trace_ray(&tra_ray, scene, n_passes, d_min, d_max)), 1 -
																											 inter->obj->transperancy);

		 // adding lighting + reflections
		light_effects(ray, scene, &c, inter);
		ref_ray = make_ray(inter->contact, v_normalize(inter->ref_dir), ray->inside);
		ref_coeff = bound(inter->obj->reflectivity / cos(inter->incidence_ang0) / 1, inter->obj->reflectivity, 1);
		if (n_passes > 1 && ref_coeff)
			c = rgb_add_weighted(c, trace_ray(&ref_ray, scene, n_passes - 1, EPS, MAX_DIST),
						1 - ref_coeff);
		free(inter);
	   	return (c);
	}
	return (BG_COLOR);
}