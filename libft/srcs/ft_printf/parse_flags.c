/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:42:45 by pfelipa           #+#    #+#             */
/*   Updated: 2020/09/02 18:56:32 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	parse_flags(t_param *params)
{
	char c;

	c = *params->s;
	while (ft_strchr("-+ 0'#", c))
	{
		if (c == '-')
			params->flags = params->flags | F_MINUS;
		else if (c == '+')
			params->flags = params->flags | F_PLUS;
		else if (c == ' ')
			params->flags = params->flags | F_SPACE;
		else if (c == '0')
			params->flags = params->flags | F_ZERO;
		else if (c == '\'')
			params->flags = params->flags | F_APOSTROPHE;
		else if (c == '#')
			params->flags = params->flags | F_HASH;
		c = *++params->s;
	}
}
