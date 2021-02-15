/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:42:45 by pfelipa           #+#    #+#             */
/*   Updated: 2020/09/02 18:56:32 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char			*ft_revstring(char *s)
{
	int		len;
	int		i;
	char	temp;

	len = ft_strlen(s);
	i = 0;
	while (i < len / 2)
	{
		temp = s[i];
		s[i] = s[len - 1 - i];
		s[len - 1 - i] = temp;
		i++;
	}
	return (s);
}

static int			ft_ndigits(int n, char *base)
{
	int		res;
	int		baselen;
	long	x;

	baselen = ft_strlen(base);
	x = (long)n;
	res = 1;
	if (x < 0)
		return (8);
	while (x > baselen - 1)
	{
		x /= baselen;
		res++;
	}
	return (res);
}

char				*ft_itoa_x(unsigned int n)
{
	char	*res;
	char	*ptr;
	long	pos;
	char	*base;

	base = "0123456789abcdef";
	if (!(res = ft_calloc(ft_ndigits(n, base) + 1, sizeof(char))))
		return (NULL);
	ptr = res;
	pos = (n < 0) ? -(long)n : (long)n;
	*ptr = '0';
	while (pos > 0)
	{
		*ptr = base[pos % 16];
		pos /= 16;
		ptr++;
	}
	res = ft_revstring(res);
	return (res);
}
