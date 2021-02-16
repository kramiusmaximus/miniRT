/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                           :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:42:45 by pfelipa           #+#    #+#             */
/*   Updated: 2020/09/02 18:56:32 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double pow(double a, int b)
{
	if (a == 0)
		return (0);
	if (b == 0)
		return (1);
	return (a * pow(a, b - 1));
}

double ft_atof(const char *str)
{
	double 		res;
	double 		neg;
	const char 	*p;

	p = NULL;
	res = 0;
	neg = 1;
	while (*str == ' ')
		str++;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg *= -1;
		str++;
	}
	while (ft_isdigit(*str) || *str == '.')
	{
		if (*str == '.')
		{
			p = str++;
			continue ;
		}
			res = res * 10 + (double)(*str++ - '0');
	}
	if (p)
		res /= pow(10, (str - p - 1));
	return (neg * res);
}