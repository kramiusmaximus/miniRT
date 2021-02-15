/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:42:45 by pfelipa           #+#    #+#             */
/*   Updated: 2020/09/02 18:56:32 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	parse(t_param *params)
{
	if (ft_strchr("-+ 0'#", *params->s))
		parse_flags(params);
	if (ft_isdigit(*params->s) || *params->s == '*')
		parse_width(params);
	if (*params->s == '.')
		parse_precision(params);
	if (ft_strchr("cspdiuxX%nfge", *params->s))
		params->type = *params->s++;
}
