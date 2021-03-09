/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:46:44 by pfelipa           #+#    #+#             */
/*   Updated: 2021/03/08 17:46:45 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	initiate_lvars(t_lvars *lvars, t_scene *scene)
{
	lvars->diff = 0;
	lvars->spec = 0;
	lvars->p = scene->light;
}

static void	light_calculations(t_lvars *lvars, t_ray *ray, t_scene *scene)
{
	lvars->light = lvars->p->content;
	lvars->l = v_normlz(v_sub(lvars->light->coords, ray->intersect->contact));
	lvars->dist = v_norm(v_sub(lvars->light->coords, ray->intersect->contact));
	lvars->ray_l = make_ray(ray->intersect->contact, lvars->l, 0);
	lvars->pass = 1;
	lvars->d[0] = EPS;
	lvars->d[1] = lvars->dist - EPS;
	if ((lvars->inter_l = trace_ray(&lvars->ray_l, \

									scene, lvars->d)))
	{
		lvars->pass = lvars->inter_l->obj->transperancy *\
		max_f(pow(1 - lvars->inter_l->ref_coeff, 0.1), 0.7);
		free(lvars->inter_l);
	}
	lvars->dot = v_dot(ray->intersect->surface_v, lvars->l);
	lvars->dot = lvars->dot < 0 ? 0 : lvars->dot;
}

void		light_effects(t_ray *ray, t_scene *scene,\
			int *c, t_intersect *inter)
{
	t_lvars		lvars;

	initiate_lvars(&lvars, scene);
	lvars.amb = rgb_smult(scene->ambient.color, scene->ambient.intensity);
	while (lvars.p)
	{
		light_calculations(&lvars, ray, scene);
		lvars.diff = rgb_add(rgb_smult(lvars.light->color,\
		lvars.dot * lvars.light->intensity * lvars.pass), lvars.diff);
		lvars.spec = rgb_add(rgb_smult(lvars.light->color,\
		(pow(200, -(200 / lvars.dot - 200))) *\
		lvars.light->intensity * lvars.pass), lvars.spec);
		lvars.p = lvars.p->next;
	}
	lvars.diff = rgb_add(lvars.diff, lvars.amb);
	*c = rgb_add_weighted(*c, rgb_multiply(*c,\
	lvars.diff), inter->obj->transperancy);
	if (!(inter->obj->type & (SQ | PL)) && inter->ref_coeff)
		*c = rgb_add(*c, lvars.spec);
}
