/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_precision_o.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:42:45 by pfelipa           #+#    #+#             */
/*   Updated: 2020/09/02 18:56:32 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*add_precision_o(char *res, t_param *params)
{
	int		bufflen;
	char	*tmp;

	if (!res || !params)
		return (res);
	bufflen = params->precision_val - ft_strlen(res);
	if (bufflen > 0)
	{
		tmp = res;
		res = ft_calloc(bufflen + ft_strlen(res) + 1, 1);
		ft_memset(res, '0', bufflen);
		ft_memcpy(res + bufflen, tmp, ft_strlen(res));
	}
	return (res);
}
