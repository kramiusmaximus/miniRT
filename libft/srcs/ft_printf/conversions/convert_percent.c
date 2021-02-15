/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_percent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:42:45 by pfelipa           #+#    #+#             */
/*   Updated: 2020/09/02 18:56:32 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*convert_percent(t_param *params)
{
	char *res;
	char *tmp;

	if (!params)
		return (NULL);
	if (!(res = malloc(sizeof(char) * 2)))
		return (res);
	ft_strlcpy(res, "%", 2);
	tmp = res;
	if (params->flags & F_PRECISION)
		res = add_precision_o(res, params);
	if (tmp != res)
		free(tmp);
	tmp = res;
	res = add_width(res, params);
	if (tmp != res)
		free(tmp);
	return (res);
}
