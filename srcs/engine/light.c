#include "miniRT.h"

void light_effects(t_ray *ray, t_scene *scene, int *c, t_intersect *inter)
{
	t_v 		l;
	t_list 		*p;
	t_light 	*light;
	t_intersect *inter_l;
	t_ray 		ray_l;
	double 		dot;
	double 		dist;
	double		transp;
	int 		a[2];

	a[0] = rgb_multiply_scalar(scene->ambient.color, scene->ambient.intensity);
	a[1] = 0;
	transp = 1;
	p = scene->light;
	while (p)
	{
		light = p->content;
		l = v_normalize(v_subtract(light->coordinates, ray->intersect->contact));
		dist = v_norm(v_subtract(light->coordinates, ray->intersect->contact));
		ray_l = make_ray(ray->intersect->contact, l, 0);
		// calculating diffuse lighting
		if ((inter_l = trace_result(&ray_l, scene, EPS, dist - EPS)))
		{
			transp = bound(inter_l->obj->transperancy, 0, 0.95);
			free(inter_l);
		}

		dot = v_dot(ray->intersect->surface_v, l);
		dot = dot < 0 ? 0 : dot;
		a[0] = rgb_add(rgb_multiply_scalar(light->color, dot * light->intensity * transp), a[0]); // diffuse
		a[1] = rgb_add(rgb_multiply_scalar(light->color, (pow(200, -(200 / dot - 200))) * light->intensity * transp),
					   a[1]); // specular

		p = p->next;
	}
	*c = rgb_add_weighted(*c, rgb_multiply(*c, a[0]), inter->obj->transperancy);
	if (!(inter->obj->type & (SQ | PL)) && inter->obj->reflectivity)
		*c = rgb_add(*c, a[1]);
}
