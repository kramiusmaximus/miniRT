#include "miniRT.h"

void process_light(t_ray *ray, t_scene *scene, int *c)
{
	t_v 		l;
	int 		l_color;
	t_list 		*p;
	t_light 	*light;
	t_ray 		ray_l;
	double 		dot;
	double 		dist;

	c[1] = rgb_multiply_scalar(scene->ambient.color, scene->ambient.intensity);
	p = scene->light;
	while (p)
	{
		light = p->content;
		l = v_normalize(v_subtract(light->coordinates, ray->intersect->contact));
		dist = v_norm(v_subtract(light->coordinates, ray->intersect->contact));
		ray_l = make_ray(ray->intersect->contact, l, 0);
		if (!trace_result(&ray_l, scene, EPS, dist - EPS))
		{
			// calculating diffuse lighting
			dot = v_dot(ray->intersect->surface_v, l);
			dot = dot < 0 ? 0 : dot;
			c[1] = rgb_add(rgb_multiply_scalar(light->color, dot * light->intensity), c[1]); // diffuse
			c[2] = rgb_add(rgb_multiply_scalar(light->color, (pow(200, -(200 / dot - 200))) * light->intensity), c[2]); // specular
		}
		p = p->next;
	}
}
