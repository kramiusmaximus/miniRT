/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:14:50 by pfelipa           #+#    #+#             */
/*   Updated: 2021/03/09 14:14:52 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	process_t_trans(t_object *obj, t_intersect *inter, t_ray *ray)
{
	double	c;
	double	r;
	double	r0;

	c = -v_dot(inter->surface_v, v_normlz(ray->dir));
	if (obj->type & (SP | CY) && obj->transperancy)
	{
		r = ray->inside ? inter->obj->refraction : 1 / inter->obj->refraction;
		if (1 - r * r * (1 - c * c) >= 0)
		{
			inter->tra_dir = v_add(v_smult(v_normlz(ray->dir), r),\
			v_smult(inter->surface_v, r * c - sqrt(1 - r * r * (1 - c * c))));
			r0 = obj->reflectivity / 4;
		}
		else
			r0 = 1;
	}
	else
	{
		inter->tra_dir = ray->dir;
		r0 = obj->reflectivity;
	}
	inter->ref_coeff = r0 == 1 || r0 == 0 ? r0 : r0 +\
	(1 - r0) * pow(1 - cos(inter->incidence_ang0), 5);
}

t_intersect	*process_t(t_object *obj, t_ray *ray, t_t *t, t_scene *scene)
{
	t_intersect *inter;

	inter = NULL;
	if (!ray || !obj || !t || !(inter = malloc(sizeof(t_intersect))))
		error("Failed malloc allocatoin.", scene);
	if (t->size == 2 && (t->arr[0] < -EPS || t->arr[1] < -EPS))
		ray->inside = 1;
	inter->t = t->closest;
	inter->contact = v_add(ray->orgn, v_smult(ray->dir, inter->t));
	inter->obj = obj;
	inter->surface_v = surface_vector(inter, obj);
	inter->surface_v = v_dot(inter->surface_v, v_normlz(ray->dir)) > 0 ?\
	v_smult(inter->surface_v, -1) : inter->surface_v;
	inter->incidence_ang0 = M_PI - acos(v_dot(v_normlz(ray->dir),\
	inter->surface_v));
	inter->ref_dir = v_sub(ray->dir, v_smult(inter->surface_v,\
	2 * v_dot(inter->surface_v, ray->dir)));
	process_t_trans(obj, inter, ray);
	return (inter);
}

t_ray		make_ray(t_v origin, t_v dir, int inside)
{
	t_ray ray;

	ray.orgn = origin;
	ray.dir = dir;
	ray.inside = inside;
	ray.intersect = NULL;
	return (ray);
}

int			swap(double *a, double *b)
{
	double temp;

	if (!a || !b)
		return (1);
	temp = *a;
	*a = *b;
	*b = temp;
	return (0);
}

void		ft_lstcclear(t_listc **lst)
{
	t_listc *current;
	t_listc *next;

	if (lst && *lst)
	{
		current = *lst;
		while (current != *lst)
		{
			next = current->next;
			free(current->cntnt);
			free(current);
			current = next;
		}
		*lst = NULL;
	}
}
