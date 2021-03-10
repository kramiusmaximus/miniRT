/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_shapes1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:21:35 by pfelipa           #+#    #+#             */
/*   Updated: 2021/03/08 17:21:36 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		ray_intersect_sphere(t_ray *ray, t_object *sp_obj, t_t *t)
{
	double		coeff[3];
	t_sp		*sp;

	if (!ray || !sp_obj || !t)
		return (1);
	sp = &sp_obj->item.sp;
	coeff[0] = v_dot(ray->dir, ray->dir);
	coeff[1] = 2 * v_dot(v_sub(ray->orgn, sp->coord), ray->dir);
	coeff[2] = v_dot(v_sub(ray->orgn, sp->coord),\
	v_sub(ray->orgn, sp->coord)) - pow(sp->diameter / 2, 2);
	solve_quadratic(coeff[0], coeff[1], coeff[2], t);
	return (0);
}

int		ray_intersect_plane(t_ray *ray, t_object *pl_obj, t_t *t)
{
	double	nom;
	double	denom;
	double	res;
	t_pl	*pl;

	if (!ray || !pl_obj || !t)
		return (1);
	pl = &pl_obj->item.pl;
	nom = v_dot(pl->norm, v_sub(pl->coord, ray->orgn));
	denom = v_dot(pl->norm, ray->dir);
	if (!isinf(res = nom / denom))
	{
		t->size = 1;
		t->arr[0] = res;
	}
	return (0);
}

int		ray_intersect_sq(t_ray *ray, t_object *sq_obj, t_t *t)
{
	t_ray_inter	stuff;
	t_sq		*sq;

	if (!ray || !sq_obj || !t)
		return (1);
	sq = &sq_obj->item.sq;
	stuff.d[0] = v_dot(sq->norm, v_sub(sq->coord, ray->orgn));
	stuff.d[1] = v_dot(sq->norm, ray->dir);
	if (!isinf(stuff.d[2] = stuff.d[0] / stuff.d[1]))
	{
		stuff.v[0] = v_add(ray->orgn, v_smult(ray->dir, stuff.d[2]));
		stuff.v[1] = v_sub(stuff.v[0], sq->coord);
		stuff.d[3] = v_dot(stuff.v[1], get_component(sq->basis, 2));
		stuff.d[4] = v_dot(stuff.v[1], v_normlz(v_x(\
		get_component(sq->basis, 2), sq->norm)));
		stuff.d[5] = sq->side_len / 2;
		if (stuff.d[3] < stuff.d[5] && stuff.d[3] > -stuff.d[5]\
		&& stuff.d[4] < stuff.d[5] && stuff.d[4] > -stuff.d[5])
		{
			t->size = 1;
			t->arr[0] = stuff.d[2];
		}
	}
	return (0);
}

int		ray_intersect_tr(t_ray *ray, t_object *tr_obj, t_t *t)
{
	t_ray_inter s;
	t_tr		*tr;
	t_object	pl_obj;

	tr = &tr_obj->item.tr;
	pl_obj.item.pl.norm = v_x(v_sub(tr->p[2], tr->p[1]),\
	v_sub(tr->p[1], tr->p[0]));
	pl_obj.item.pl.coord = tr->p[0];
	ray_intersect_plane(ray, &pl_obj, t);
	if (t->size)
	{
		s.v[3] = v_add(ray->orgn, v_smult(ray->dir, t->arr[0]));
		s.i = 0;
		while (s.i < 3)
		{
			s.v[4] = v_normlz(v_sub(tr->p[(s.i + 1) % 3], tr->p[s.i]));
			s.v[5] = v_normlz(v_sub(tr->p[(s.i + 2) % 3], tr->p[s.i]));
			s.v[6] = v_normlz(v_sub(s.v[3], tr->p[s.i++]));
			s.d[0] = v_dot(s.v[4], s.v[5]);
			if (v_dot(s.v[6], s.v[4]) < s.d[0]\
			|| v_dot(s.v[6], s.v[5]) < s.d[0])
				t->size = 0;
		}
	}
	return (0);
}
