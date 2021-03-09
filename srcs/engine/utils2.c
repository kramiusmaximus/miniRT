/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:15:08 by pfelipa           #+#    #+#             */
/*   Updated: 2021/03/09 14:15:09 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			selection_sort(double arr[], int size)
{
	int		i;
	int		j;
	double	min;

	if (!arr)
		return (1);
	i = 0;
	while (i < size)
	{
		min = arr[i];
		j = i + 1;
		while (j < size)
		{
			if (arr[j] < min)
			{
				swap(&arr[i], &arr[j]);
				min = arr[j];
			}
			j++;
		}
		i++;
	}
	return (0);
}

t_v			v_make(double x, double y, double z)
{
	t_v res;

	res.v[0] = x;
	res.v[1] = y;
	res.v[2] = z;
	return (res);
}

t_m			m_i(int n)
{
	int i;
	int j;
	t_m	m;

	m.size[0] = n;
	m.size[1] = n;
	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < n)
		{
			m.m[i][j] = i == j ? 1 : 0;
			j++;
		}
		i++;
	}
	return (m);
}

t_m			dir_to_rot_mat(t_v dir)
{
	double	rot[3];
	t_m 	m;

	m = m_i(3);
	rot[0] = atan(dir.v[1] / dir.v[2]);
	if (dir.v[2] < EPS && dir.v[2] > -EPS)
		rot[0] = atan(dir.v[1] / EPS);
	m = rotate_xyz(rot[0], 0, 0, m);

	rot[1] = atan(dir.v[0] / dir.v[2]);
	if (dir.v[2] < EPS && dir.v[2] > -EPS)
		rot[1] = atan(dir.v[0] / EPS);
	if (dir.v[2] < 0)
	{
		rot[1] += M_PI;
		//rot[0] *= -1;
	}
	m = rotate_xyz(0, rot[1], 0, m);
	return (m);
}

t_m			norm_to_rot_mat(t_m basis, t_v norm)
{
	double rot[3];

	rot[0] = atan(sqrt(pow(norm.v[2], 2) + pow(norm.v[0], 2)) / norm.v[1]);
	if (norm.v[1] < EPS && norm.v[1] > -EPS)
		rot[0] = atan(sqrt(pow(norm.v[2], 2) + pow(norm.v[0], 2)) / EPS);
	if (norm.v[1] < 0)
		rot[0] += M_PI;
	basis = rotate_xyz(rot[0], 0, 0, basis);


	rot[1] = atan(norm.v[0] / norm.v[2]);
	if (norm.v[2] < EPS && norm.v[2] > -EPS)
		rot[1] = atan(norm.v[0] / EPS);
	if (norm.v[2] < 0)
		rot[1] += M_PI;
	basis = rotate_xyz(0, rot[1], 0, basis);
	return (basis);
}
