/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:53:24 by pfelipa           #+#    #+#             */
/*   Updated: 2021/03/08 17:53:26 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_m			m_transpose(t_m m)
{
	t_m	trans;
	int	i;
	int	j;

	if (m.size[0] != m.size[1])
		ft_printf("dims sizes are not equal\n");
	i = 0;
	m.size[0] = 3;
	m.size[1] = 3;
	while (i < m.size[0])
	{
		j = 0;
		while (j < m.size[0])
		{
			trans.m[i][j] = m.m[j][i];
			j++;
		}
		i++;
	}
	return (trans);
}

double		max_f(double a, double b)
{
	return (a > b ? a : b);
}

double		min_f(double a, double b)
{
	return (a < b ? a : b);
}

double		abs_f(double a)
{
	return (a > 0 ? -a : a);
}

double		bound(double num, double lower_b, double upper_b)
{
	if (num > upper_b)
		return (upper_b);
	if (num < lower_b)
		return (lower_b);
	return (num);
}
