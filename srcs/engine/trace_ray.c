/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 13:27:43 by pfelipa           #+#    #+#             */
/*   Updated: 2021/03/09 13:27:49 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tcl.h>
#include "minirt.h"

static void		initiate_trvars(t_trvars *trvars,\
t_scene *scene, double max_d)
{
	ft_bzero(trvars, sizeof(t_trvars));
	trvars->t.closest = max_d;
	trvars->p = scene->object;
	trvars->obj_closest = NULL;
}

static int		ray_intersect_wrapper(t_ray *ray, t_trvars *trvars)
{
	int	i;

	i = 0;
	if (trvars->obj->type & SP)
		i = ray_intersect_sphere(ray, trvars->obj, &trvars->t);
	else if (trvars->obj->type & PL)
		i = ray_intersect_plane(ray, trvars->obj, &trvars->t);
	else if (trvars->obj->type & SQ)
		i = ray_intersect_sq(ray, trvars->obj, &trvars->t);
	else if (trvars->obj->type & CY)
		i = ray_intersect_cy(ray, trvars->obj, &trvars->t);
	else if (trvars->obj->type & TR)
		i = ray_intersect_tr(ray, trvars->obj, &trvars->t);
	return (i);
}

t_intersect		*trace_ray(t_ray *ray, t_scene *scene, double *d)
{
	t_trvars	trvars;

	initiate_trvars(&trvars, scene, d[1]);
	while (trvars.p)
	{
		trvars.obj = trvars.p->content;
		trvars.t.size = 0;
		if (ray_intersect_wrapper(ray, &trvars))
			error("Error in calculating\\"
			"intersection or ray and shapes.", scene);
		trvars.i = 0;
		while (trvars.i < trvars.t.size)
		{
			if (trvars.t.arr[trvars.i] >\
			d[0] && trvars.t.arr[trvars.i] < trvars.t.closest)
			{
				trvars.t.closest = trvars.t.arr[trvars.i];
				trvars.obj_closest = trvars.obj;
			}
			trvars.i++;
		}
		trvars.p = trvars.p->next;
	}
	return (trvars.obj_closest ? (ray->intersect =\
	process_t(trvars.obj_closest, ray, &trvars.t, scene)) : NULL);
}

int				trace_color(t_ray *ray, t_scene *scene, int n_passes, double *d)
{
	t_intersect	*inter;
	int			c;
	t_ray		r[2];

	if ((inter = trace_ray(ray, scene, d)))
	{
		d[0] = EPS;
		c = inter->obj->color;
		r[0] = make_ray(inter->contact, v_normlz(inter->tra_dir),\
		(inter->obj->type & (SP | CY)) ? ray->inside ^ 0b1 : ray->inside);
		if (n_passes > 1 && inter->obj->transperancy && inter->ref_coeff < 1)
			c = rgb_add_weighted(c, rgb_multiply(c, trace_color(&r[0],\
			scene, n_passes - 1, d)), 1 - inter->obj->transperancy);
		light_effects(ray, scene, &c, inter);
		r[1] = make_ray(inter->contact, v_normlz(inter->ref_dir), ray->inside);
		if (n_passes > 1 && inter->ref_coeff)
			c = rgb_add_weighted(c, trace_color(&r[1], scene, n_passes - 1, d),
						1 - inter->ref_coeff);
		free(inter);
		return (c);
	}
	return (BG_COLOR);
}
