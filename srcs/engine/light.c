#include "miniRT.h"


static void initiate_lvars(t_lvars *lvars, t_scene *scene)
{
	lvars->diff = 0;
	lvars->spec = 0;
	lvars->p = scene->light;
}

static void light_calculations(t_lvars *lvars, t_ray *ray, t_scene *scene)
{
	lvars->light = lvars->p->content;
	lvars->l = v_normalize(v_subtract(lvars->light->coordinates, ray->intersect->contact));
	lvars->dist = v_norm(v_subtract(lvars->light->coordinates, ray->intersect->contact));
	lvars->ray_l = make_ray(ray->intersect->contact, lvars->l, 0);
	lvars->transp = 1;
	if ((lvars->inter_l = trace_ray(&lvars->ray_l, scene, EPS, lvars->dist - EPS)))
	{
		lvars->transp = bound(lvars->inter_l->obj->transperancy, 0, 0.95);
		free(lvars->inter_l);
	}
	lvars->dot = v_dot(ray->intersect->surface_v, lvars->l);
	lvars->dot = lvars->dot < 0 ? 0 : lvars->dot;
}

void light_effects(t_ray *ray, t_scene *scene, int *c, t_intersect *inter)
{
	t_lvars		lvars;

	initiate_lvars(&lvars, scene);
	lvars.amb = rgb_multiply_scalar(scene->ambient.color, scene->ambient.intensity);
	while (lvars.p)
	{
		light_calculations(&lvars, ray, scene);
		lvars.diff = rgb_add(rgb_multiply_scalar(lvars.light->color, lvars.dot * lvars.light->intensity * lvars.transp), lvars.diff);
		lvars.spec = rgb_add(rgb_multiply_scalar(lvars.light->color, (pow(200, -(200 / lvars.dot - 200))) * lvars.light->intensity * lvars.transp),
							 lvars.spec);
		lvars.p = lvars.p->next;
	}
	lvars.diff = rgb_add(lvars.diff, lvars.amb);
	*c = rgb_add_weighted(*c, rgb_multiply(*c, lvars.diff), inter->obj->transperancy);
	if (!(inter->obj->type & (SQ | PL)) && inter->obj->reflectivity)
		*c = rgb_add(*c, lvars.spec);
}
