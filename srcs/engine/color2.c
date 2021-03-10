/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:04:19 by pfelipa           #+#    #+#             */
/*   Updated: 2021/03/08 17:04:20 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rgb_multiply(int c1, int c2)
{
	int t;
	int r;
	int g;
	int b;

	t = get_t(c1);
	r = get_r(c1) * get_r(c2) / 255;
	g = get_g(c1) * get_g(c2) / 255;
	b = get_b(c1) * get_b(c2) / 255;
	return (rgb_create(t, r, g, b));
}

int	rgb_smult(int c1, double s)
{
	int t;
	int r;
	int g;
	int b;

	t = get_t(c1);
	r = (int)((double)get_r(c1) * s);
	g = (int)((double)get_g(c1) * s);
	b = (int)((double)get_b(c1) * s);
	return (rgb_create(t, r, g, b));
}

int	rgb_add(int c1, int c2)
{
	int t;
	int r;
	int g;
	int b;

	t = get_t(c1);
	r = get_r(c1) + get_r(c2);
	g = get_g(c1) + get_g(c2);
	b = get_b(c1) + get_b(c2);
	return (rgb_create(t, r, g, b));
}

int	rgb_add_weighted(int c1, int c2, double w)
{
	int t;
	int r;
	int g;
	int b;

	t = get_t(c1);
	r = rgb_smult(get_r(c1), w)\
	+ rgb_smult(get_r(c2), 1 - w);
	g = rgb_smult(get_g(c1), w)\
	+ rgb_smult(get_g(c2), 1 - w);
	b = rgb_smult(get_b(c1), w)\
	+ rgb_smult(get_b(c2), 1 - w);
	return (rgb_create(t, r, g, b));
}

int	rgb_avg(int arr[], int n)
{
	int rgb[3];
	int avg;
	int i;

	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	i = 0;
	while (i < n)
	{
		rgb[0] += get_r(arr[i]);
		rgb[1] += get_g(arr[i]);
		rgb[2] += get_b(arr[i]);
		i++;
	}
	avg = rgb_create(0, rgb[0] / n, rgb[1] / n, rgb[2] / n);
	return (avg);
}
