#include <tcl.h>
#include "miniRT.h"

static void 		initiate_trvars(t_trvars *trvars, t_scene *scene, double max_d)
{
	ft_bzero(trvars, sizeof(t_trvars));
	trvars->t.closest = max_d;
	trvars->p = scene->object;
	trvars->obj_closest = NULL;
}

static void 		ray_intersect_wrapper(t_ray *ray, t_trvars *trvars)
{
	if (trvars->obj->type & SP)
		ray_intersect_sphere(ray, trvars->obj, &trvars->t);
	else if (trvars->obj->type & PL)
		ray_intersect_plane(ray, trvars->obj, &trvars->t);
	else if (trvars->obj->type & SQ)
		ray_intersect_sq(ray, trvars->obj, &trvars->t);
	else if (trvars->obj->type & CY)
		ray_intersect_cy(ray, trvars->obj, &trvars->t);
	else if (trvars->obj->type & TR)
		ray_intersect_tr(ray, trvars->obj, &trvars->t);
}

t_intersect *trace_ray(t_ray *ray, t_scene *scene, double min_d, double max_d)
{
	t_trvars	trvars;

	initiate_trvars(&trvars, scene, max_d);
	while (trvars.p)
	{
		trvars.obj = trvars.p->content;
		trvars.t.size = 0;
		ray_intersect_wrapper(ray, &trvars);
		trvars.i = 0;
		while (trvars.i < trvars.t.size)
		{
			if (trvars.t.arr[trvars.i] > min_d && trvars.t.arr[trvars.i] < trvars.t.closest)
			{
				trvars.t.closest = trvars.t.arr[trvars.i];
				trvars.obj_closest = trvars.obj;
			}
			trvars.i++;
		}
		trvars.p = trvars.p->next;
	}
	return (trvars.obj_closest ? (ray->intersect = process_t(trvars.obj_closest, ray, &trvars.t, scene)) : NULL);
}

int trace_color(t_ray *ray, t_scene *scene, int n_passes, double d_min, double d_max)
{
	t_intersect *inter;
	int 		c;
	t_ray 		r[2];
	double 		ref_coeff;

	if ((inter = trace_ray(ray, scene, d_min, d_max)))
	{
		c = inter->obj->color;
		r[0] = make_ray(inter->contact, v_normalize(inter->tra_dir), (inter->obj->type & (SP | CY)) ? ray->inside ^ 0b1 : ray->inside);
		if (n_passes > 1 && ray->inside && inter->obj->transperancy)
			return (trace_color(&r[0], scene, n_passes - 1, EPS, MAX_DIST));
		if (n_passes > 1 && inter->obj->transperancy)
				c = rgb_add_weighted(c, rgb_multiply(c, trace_color(&r[0], scene, n_passes - 1, EPS, MAX_DIST)), 1 -
																											   inter->obj->transperancy);
		light_effects(ray, scene, &c, inter);
		r[1] = make_ray(inter->contact, v_normalize(inter->ref_dir), ray->inside);
		ref_coeff = bound(inter->obj->reflectivity / cos(inter->incidence_ang0) / 1.5, inter->obj->reflectivity, 1);
		if (n_passes > 1 && ref_coeff)
			c = rgb_add_weighted(c, trace_color(&r[1], scene, n_passes - 1, EPS, MAX_DIST),
						1 - ref_coeff);
		free(inter);
	   	return (c);
	}
	return (BG_COLOR);
}
