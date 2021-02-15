/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_width.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:42:45 by pfelipa           #+#    #+#             */
/*   Updated: 2020/09/02 18:56:32 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	parse_width(t_param *params)
{
	const char	*ptr;
	char		*width;

	if (!params)
		return ;
	ptr = params->s;
	while (ft_isdigit(*params->s))
		params->s++;
	if (ptr != params->s)
	{
		if ((width = ft_substr(ptr, 0, params->s - ptr)))
		{
			params->width = ft_atoi(width);
			free(width);
		}
	}
	else if (*params->s == '*')
	{
		params->width = va_arg(params->ap, int);
		params->s++;
	}
}
