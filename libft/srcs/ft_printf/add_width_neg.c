/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_width_neg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:42:45 by pfelipa           #+#    #+#             */
/*   Updated: 2020/09/02 18:56:32 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	add_width_neg(t_param *params, char *res, int len, int bufflen)
{
	char	c;
	int		neg;

	c = ' ';
	if ((params->flags & F_ZERO) &&
		(!(params->flags & F_PRECISION) || params->precision_val < 0))
		c = '0';
	neg = *params->tmp == '-' && c == '0' ? 1 : 0;
	if (neg)
		res[0] = '-';
	ft_memset(res + neg, c, bufflen);
	ft_memcpy(res + bufflen + neg, params->tmp + neg, len);
}
