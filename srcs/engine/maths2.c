/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:53:07 by pfelipa           #+#    #+#             */
/*   Updated: 2021/03/08 17:53:09 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_v		v_smult(t_v v, double s)
{
	v.v[0] *= s;
	v.v[1] *= s;
	v.v[2] *= s;
	return (v);
}

t_v		v_normlz(t_v v)
{
	return (v_smult(v, 1 / v_norm(v)));
}

t_v		v_x(t_v v1, t_v v2)
{
	t_v	res;

	res.v[0] = v1.v[1] * v2.v[2] - v1.v[2] * v2.v[1];
	res.v[1] = v1.v[2] * v2.v[0] - v1.v[0] * v2.v[2];
	res.v[2] = v1.v[0] * v2.v[1] - v1.v[1] * v2.v[0];
	return (res);
}

double	point_line_dist(t_v x0, t_v x1, t_v p)
{
	double nom;
	double denom;

	nom = v_norm(v_x(v_sub(p, x0), v_sub(p, x1)));
	denom = v_norm(v_sub(x1, x0));
	return (nom / denom);
}
