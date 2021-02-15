/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_precision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:42:45 by pfelipa           #+#    #+#             */
/*   Updated: 2020/09/02 18:56:32 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	parse_precision(t_param *params)
{
	const char	*ptr;
	char		*precision_val;

	if (!params)
		return ;
	if (*params->s == '.')
	{
		params->flags = params->flags | F_PRECISION;
		ptr = ++params->s;
		while (ft_isdigit(*params->s))
			params->s++;
		if ((params->s - ptr > 0) && (precision_val =
			ft_substr(ptr, 0, params->s - ptr)))
		{
			params->precision_val = ft_atoi(precision_val);
			free(precision_val);
		}
		else if (*params->s == '*')
		{
			params->precision_val = va_arg(params->ap, int);
			params->s++;
		}
	}
}
