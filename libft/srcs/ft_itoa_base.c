/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:42:45 by pfelipa           #+#    #+#             */
/*   Updated: 2020/09/02 18:56:32 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int			ft_valid_base(char *s)
{
	while (*s)
	{
		if (!ft_isprint(*s++))
			return (0);
	}
	return (1);
}

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
	{
		res++;
		x *= -1;
	}
	while (x > baselen - 1)
	{
		x /= baselen;
		res++;
	}
	return (res + 1);
}

char				*ft_itoa_base(int n, char *base)
{
	char	*res;
	char	*ptr;
	int		neg;
	long	pos;
	int		baselen;

	if ((baselen = ft_strlen(base)) == 0 || !ft_valid_base(base) ||
		!(res = ft_calloc(ft_ndigits(n, base), sizeof(char))))
		return (NULL);
	ptr = res;
	neg = (n < 0) ? 1 : 0;
	pos = (n < 0) ? -(long)n : (long)n;
	*ptr = '0';
	while (pos > 0)
	{
		*ptr = base[pos % baselen];
		pos /= baselen;
		ptr++;
	}
	if (neg)
		*ptr = '-';
	res = ft_revstring(res);
	return (res);
}
