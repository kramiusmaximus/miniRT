/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_width.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:42:45 by pfelipa           #+#    #+#             */
/*   Updated: 2020/09/02 18:56:32 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*add_width(char *res, t_param *params)
{
	int		len;
	int		bufflen;

	if (!res || !params)
		return (res);
	len = ft_strlen(res);
	bufflen = ft_abs(params->width) - len;
	if (bufflen < 1)
		return (res);
	if (params->type == 'c' && !res[0])
		bufflen--;
	params->tmp = res;
	if (!(res = ft_calloc(ft_abs(params->width) + 1, 1)))
		return (NULL);
	if ((params->flags & F_MINUS) || params->width < 0)
		add_width_pos(params, res, len, bufflen);
	else
		add_width_neg(params, res, len, bufflen);
	return (res);
}
