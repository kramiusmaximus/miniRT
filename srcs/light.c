#include "miniRT.h"

int process_light(t_ray *ray, t_scene *scene)
{
	int 	light_effects;
	int 	p_effect;
	t_v l;
	t_v n;
	double 	t;
	t_light *p;
	t_intersect	*inter;
	t_ray 	ray_l;
	double 	dot;

	inter = ray->intersect;
	light_effects = rgb_multiply_scalar(scene->ambient.color, scene->ambient.intensity);
	p = scene->light;
	n = inter->surface_v;
	while (p)
	{
		t = 1;
		l = v_normalize(v_subtract(p->coordinates, inter->contact));
		ray_l = make_ray(inter->contact, l);
		if (!trace_result(&ray_l, scene, 0.000000001) &&
			v_dot(n, ray->dir) < 0)  /// actually incorrect but works for now
		{
			dot = v_dot(n, l);
			dot = dot < 0 ? 0 : dot;
			p_effect = rgb_multiply_scalar(p->color, dot * p->intensity);
			light_effects = rgb_add(light_effects, p_effect);
		}
		p = p->next;
	}
	return (light_effects);
}
