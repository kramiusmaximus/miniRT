/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:42:45 by pfelipa           #+#    #+#             */
/*   Updated: 2020/09/02 18:56:32 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*process_params(t_param *params)
{
	char *res;
	char c;

	res = NULL;
	c = params->type;
	if (c == '%')
		res = convert_percent(params);
	else if (c == 'd' || c == 'i')
		res = convert_i(params);
	else if (c == 'u')
		res = convert_u(params);
	else if (c == 'x')
		res = convert_x(params);
	else if (c == 'X')
		res = convert_xx(params);
	else if (c == 's')
		res = convert_s(params);
	else if (c == 'c')
		res = convert_c(params);
	else if (c == 'p')
		res = convert_p(params);
	return (res);
}
