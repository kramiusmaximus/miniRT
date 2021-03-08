/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:53:13 by pfelipa           #+#    #+#             */
/*   Updated: 2021/03/08 17:53:14 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			solve_quadratic(double a, double b, double c, t_t *t)
{
	double discriminant;

	if (!t)
		return (1);
	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant * 100000 == 0)
	{
		t->arr[0] = -b / (2 * a);
		t->size = 1;
	}
	else if (discriminant < 0)
		t->size = 0;
	else
	{
		t->arr[0] = (-b + sqrt(discriminant)) / (2 * a);
		t->arr[1] = (-b - sqrt(discriminant)) / (2 * a);
		t->size = 2;
	}
	return (0);
}

t_v			v_mat_mul_vec(t_m m, t_v v)
{
	int i;
	int j;
	t_v res;

	res = v_make(0, 0, 0);
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			res.v[i] += m.m[i][j] * v.v[j];
			j++;
		}
		i++;
	}
	return (res);
}
