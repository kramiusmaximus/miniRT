/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:04:07 by pfelipa           #+#    #+#             */
/*   Updated: 2021/03/08 17:04:09 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		get_t(int trgb)
{
	return ((trgb & (0xFF000000)) >> 24);
}

int		get_r(int trgb)
{
	return ((trgb & (0x00FF0000)) >> 16);
}

int		get_g(int trgb)
{
	return ((trgb & (0x0000FF00)) >> 8);
}

int		get_b(int trgb)
{
	return ((trgb & (0x000000FF)));
}

int		rgb_create(int t, int r, int g, int b)
{
	int res;

	t = t < 0 ? 0 : t;
	t = t > 255 ? 255 : t;
	r = r < 0 ? 0 : r;
	r = r > 255 ? 255 : r;
	g = g < 0 ? 0 : g;
	g = g > 255 ? 255 : g;
	b = b < 0 ? 0 : b;
	b = b > 255 ? 255 : b;
	res = (t << 24 | r << 16 | g << 8 | b);
	return (res);
}
