/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_p.c                                        :+:      :+:    :+:   */
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

static long			ft_ndigits(long n, char *base)
{
	long		res;
	long		baselen;

	baselen = ft_strlen(base);
	res = 1;
	if (n < 0)
		return (8);
	while (n > baselen - 1)
	{
		n /= baselen;
		res++;
	}
	return (res);
}

char				*ft_itoa_p(long n)
{
	char	*res;
	char	*ptr;
	long	pos;
	char	*base;

	base = "0123456789abcdef";
	if (!(res = ft_calloc(ft_ndigits(n, base) + 3, sizeof(char))))
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
	if (!n)
		ptr++;
	ft_strlcpy(ptr, "x0", 3);
	res = ft_revstring(res);
	return (res);
}
