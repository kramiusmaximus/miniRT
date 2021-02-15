/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:42:45 by pfelipa           #+#    #+#             */
/*   Updated: 2020/09/02 18:56:32 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	base_index(char c, char *base)
{
	int n;

	n = 0;
	while (base[n])
	{
		if (base[n] == c)
			return (n);
		n++;
	}
	return (-1);
}

int			ft_atoi_base(char *s, char *base)
{
	int sign;
	int res;
	int baselen;

	if (!s || !base)
		return (0);
	baselen = ft_strlen(base);
	sign = 1;
	res = 0;
	while (*s == ' ' || *s == '\t' || *s == '\n'
	|| *s == '\v' || *s == '\r' || *s == '\f')
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign *= -1;
		s++;
	}
	while (base_index(*s, base) >= 0)
	{
		if (res * baselen < res)
			return (sign == 1 ? -1 : 0);
		res = (res * baselen) + (base_index(*s++, base));
	}
	return (sign * res);
}
