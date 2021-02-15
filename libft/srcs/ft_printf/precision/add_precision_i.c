/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_precision_i.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:42:45 by pfelipa           #+#    #+#             */
/*   Updated: 2020/09/02 18:56:32 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*add_precision_i(char *res, t_param *params)
{
	int		len;
	char	*tmp;
	char	neg;

	if (!res || !params)
		return (res);
	len = ft_strlen(res);
	if ((neg = *res == '-' ? 1 : 0))
		len--;
	if (!ft_strncmp(res, "0", len) && params->precision_val == 0)
		*res = 0;
	if (params->precision_val > len)
	{
		tmp = res;
		res = ft_calloc(params->precision_val + neg + 1, 1);
		if (neg)
			res[0] = '-';
		ft_memset(res + neg, '0', params->precision_val - len);
		ft_memcpy(res + params->precision_val + neg - len, tmp + neg, len);
	}
	return (res);
}
