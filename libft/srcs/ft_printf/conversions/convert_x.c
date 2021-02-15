/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:42:45 by pfelipa           #+#    #+#             */
/*   Updated: 2020/09/02 18:56:32 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*convert_x(t_param *params)
{
	char *res;
	char *tmp;

	res = ft_itoa_x(va_arg(params->ap, unsigned int));
	tmp = res;
	if (params->flags & F_PRECISION)
		res = add_precision_i(res, params);
	if (tmp != res)
		free(tmp);
	tmp = res;
	res = add_width(res, params);
	if (tmp != res)
		free(tmp);
	return (res);
}
