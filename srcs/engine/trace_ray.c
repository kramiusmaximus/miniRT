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
	int 		c[3] = {0,0,0};
	t_ray 		ref_ray;
	t_ray 		tra_ray;
	double 		dist;
	double 		ref_coeff;

	if ((inter = trace_result(ray, scene, d_min, d_max)))
	{
		c[0] = inter->obj->color;
		process_light(ray, scene, c);
		c[1] = rgb_multiply(c[0], c[1]);
		c[0] = rgb_add(c[1], c[2]);
		tra_ray = make_ray(inter->contact, v_normalize(inter->tra_dir), !ray->inside);
		if (--n_passes && inter->obj->transperancy)
		{
			if (ray->inside)
				c[0] = rgb_add_weighted(c[0], trace_ray(&tra_ray, scene, n_passes, d_min, d_max), 1 - inter->obj->transperancy);
			else
				c[0] = rgb_add_weighted(c[0], trace_ray(&tra_ray, scene, n_passes, d_min, d_max), 0);
		}

		ref_ray = make_ray(inter->contact, v_normalize(inter->ref_dir), 0);
		ref_coeff = inter->obj->reflectivity * sin(inter->incidence_ang0);
		if (n_passes && ref_coeff)
		{

			c[0] = rgb_add_weighted(c[0], trace_ray(&ref_ray, scene, n_passes, d_min, d_max),
									1 - ref_coeff);
		}
			free(inter);
	   	return (c[0]);
	}
	return (BG_COLOR);
}