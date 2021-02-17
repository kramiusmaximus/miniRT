#include "miniRT.h"

int process_light(t_ray *ray, t_scene *scene)
{
	t_v 		l;
	int 		l_color;
	t_list 		*p;
	t_light 	*light;
	t_ray 		ray_l;
	double 		dot;

	l_color = rgb_multiply_scalar(scene->ambient.color, scene->ambient.intensity);
	p = scene->light;
	while (p)
	{
		light = p->content;
		l = v_normalize(v_subtract(light->coordinates, ray->intersect->contact));
		ray_l = make_ray(ray->intersect->contact, l);
		if (!trace_result(&ray_l, scene, EPS))  /// actually incorrect but works for now
		{
			// calculating diffuse lighting
			dot = v_dot(ray->intersect->surface_v, l);
			dot = dot < 0 ? 0 : dot;
			l_color = rgb_add(rgb_multiply_scalar(light->color, dot * light->intensity), l_color); // diffuse
			l_color = rgb_add(rgb_multiply_scalar(light->color, (pow(dot, 60)) * light->intensity), l_color); // specular
		}
		p = p->next;
	}
	return (l_color);
}
