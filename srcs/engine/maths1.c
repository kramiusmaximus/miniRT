/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:53:02 by pfelipa           #+#    #+#             */
/*   Updated: 2021/03/08 17:53:04 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_v		v_create(double x1, double x2, double x3)
{
	t_v v;

	v.v[0] = x1;
	v.v[1] = x2;
	v.v[2] = x3;
	return (v);
}

t_v		v_add(t_v v1, t_v v2)
{
	v1.v[0] += v2.v[0];
	v1.v[1] += v2.v[1];
	v1.v[2] += v2.v[2];
	return (v1);
}

t_v		v_sub(t_v v1, t_v v2)
{
	v1.v[0] -= v2.v[0];
	v1.v[1] -= v2.v[1];
	v1.v[2] -= v2.v[2];
	return (v1);
}

double	v_dot(t_v v1, t_v v2)
{
	return (v1.v[0] * v2.v[0] + v1.v[1] * v2.v[1] + v1.v[2] * v2.v[2]);
}

double	v_norm(t_v v)
{
	return (sqrt(pow(v.v[0], 2) + pow(v.v[1], 2) + pow(v.v[2], 2)));
}
