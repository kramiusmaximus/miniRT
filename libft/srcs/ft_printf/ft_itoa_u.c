/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_u.c                                        :+:      :+:    :+:   */
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

static int			ft_ndigits(unsigned int n)
{
	int		res;
	long	x;

	x = (long)n;
	res = 1;
	if (x < 0)
		return (8);
	while (x > 9)
	{
		x /= 10;
		res++;
	}
	return (res);
}

char				*ft_itoa_u(unsigned int n)
{
	char	*res;
	char	*ptr;
	long	pos;

	if (!(res = ft_calloc(ft_ndigits(n) + 1, sizeof(char))))
		return (NULL);
	ptr = res;
	pos = (n < 0) ? -(long)n : (long)n;
	*ptr = '0';
	while (pos > 0)
	{
		*ptr = pos % 10 + '0';
		pos /= 10;
		ptr++;
	}
	res = ft_revstring(res);
	return (res);
}
