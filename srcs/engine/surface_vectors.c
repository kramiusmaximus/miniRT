/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface_vectors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 13:25:31 by pfelipa           #+#    #+#             */
/*   Updated: 2021/03/09 13:25:32 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_v	surface_vector_cy(t_intersect *inter, t_object *cy_obj)
{
	t_cy	*cy;
	double	x;
	t_v		xp;
	double	k;

	cy = &cy_obj->item.cy;
	k = v_dot(v_sub(inter->contact, cy->coord),\
	cy->norm) / v_norm(v_sub(inter->contact, cy->coord));
	x = ((cy->diameter / 2) * k) / sqrt(1 - pow(k, 2));
	xp = v_sub(inter->contact, v_add(cy->coord, v_smult(cy->norm, x)));
	if (point_line_dist(cy->coord, v_add(cy->coord, v_smult(cy->norm, cy->h)),\
	inter->contact)
	< cy->diameter / 2 - EPS)
		return (cy->norm);
	return (v_normlz(xp));
}

t_v			surface_vector(t_intersect *inter, t_object *obj)
{
	t_v	n;

	n = v_create(0, 0, 0);
	if (obj->type & SP)
		n = v_normlz(v_sub(inter->contact, obj->item.sp.coord));
	else if (obj->type & PL)
		n = obj->item.pl.norm;
	else if (obj->type & SQ)
		n = obj->item.sq.norm;
	else if (obj->type & CY)
		n = surface_vector_cy(inter, obj);
	else if (obj->type & TR)
		n = v_normlz(v_x(v_sub(obj->item.tr.p[0], obj->item.tr.p[1]),\
		v_sub(obj->item.tr.p[1], obj->item.tr.p[2])));
	return (n);
}
