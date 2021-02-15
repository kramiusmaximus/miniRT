/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:42:45 by pfelipa           #+#    #+#             */
/*   Updated: 2020/09/02 18:56:32 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*convert_c(t_param *params)
{
	char *res;
	char *tmp;

	if (!(res = ft_calloc(2, 1)))
		return (NULL);
	res[0] = va_arg(params->ap, int);
	if (!res[0])
		params->out++;
	tmp = res;
	if (params->flags & F_PRECISION)
		res = add_precision_s(res, params);
	if (tmp != res)
		free(tmp);
	tmp = res;
	res = add_width(res, params);
	if (tmp != res)
		free(tmp);
	return (res);
}
