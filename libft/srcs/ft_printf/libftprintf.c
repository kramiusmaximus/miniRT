/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:42:45 by pfelipa           #+#    #+#             */
/*   Updated: 2020/09/02 18:56:32 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_printf(const char *s, ...)
{
	t_param	params;

	ft_bzero(&params, sizeof(params));
	params.s = s;
	params.out = 0;
	if (!s)
		return (params.out);
	va_start(params.ap, s);
	while (*params.s)
	{
		if (*params.s == '%')
		{
			params.s++;
			if (!(params.s = process_arg(&params)))
				return (params.out);
		}
		else
		{
			params.out++;
			ft_putchar_fd(*params.s++, 1);
		}
	}
	va_end(params.ap);
	return (params.out);
}
