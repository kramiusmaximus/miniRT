#include "miniRT.h"

int process_light(t_ray *ray, t_scene *scene)
{
	t_v 		l;
	int 		l_color;
	t_v 		n;
	double 		t;
	t_light 	*p;
	t_intersect	*inter;
	t_ray 		ray_l;
	double 		dot;

	inter = ray->intersect;
	l_color = rgb_multiply_scalar(scene->ambient.color, scene->ambient.intensity);
	p = scene->light;
	//n = v_dot(inter->surface_v , ray->dir) > 0 ? v_scalar_mult(inter->surface_v,-1) : inter->surface_v;
	while (p)
	{
		t = 1;
		l = v_normalize(v_subtract(p->coordinates, inter->contact));
		ray_l = make_ray(inter->contact, l);
		if (!trace_result(&ray_l, scene, EPS))  /// actually incorrect but works for now
		{
			// calculating diffuse lighting
			dot = v_dot(inter->surface_v, l);
			l_color = rgb_add(rgb_multiply_scalar(p->color, dot * p->intensity), l_color); // diffuse lighitng
			l_color = rgb_add(rgb_multiply_scalar(p->color, (pow(dot, 300)) * p->intensity), l_color); // specular
			// lighting
		}
		p = p->next;
	}
	return (l_color);
}
