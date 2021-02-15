/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:42:45 by pfelipa           #+#    #+#             */
/*   Updated: 2020/09/02 18:56:32 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LIBFTPRINTF_H
# define _LIBFTPRINTF_H
# define F_MINUS       (0b00000001)
# define F_PLUS        (0b00000010)
# define F_SPACE       (0b00000100)
# define F_ZERO  	   (0b00001000)
# define F_APOSTROPHE  (0b00010000)
# define F_HASH		   (0b00100000)
# define F_PRECISION   (0b01000000)
# include "libft.h"
# include <stdarg.h>

typedef struct	s_param
{
	va_list		ap;
	const char	*s;
	int			out;
	char		flags;
	int			width;
	int			precision_val;
	char		type;
	char		*tmp;
}				t_param;
int				ft_printf(const char *s, ...);
const char		*process_arg(t_param *params);
void			initiate_params(t_param *obj);
void			parse(t_param *params);
void			parse_flags(t_param *params);
void			parse_width(t_param *params);
void			parse_precision(t_param *params);
char			*process_params(t_param *params);
char			*convert_percent(t_param *params);
char			*convert_s(t_param *params);
char			*convert_c(t_param *params);
char			*convert_p(t_param *params);
char			*convert_i(t_param *params);
char			*convert_x(t_param *params);
char			*convert_xx(t_param *params);
char			*convert_u(t_param *params);
char			*add_precision_s(char *res, t_param *params);
char			*add_precision_i(char *res, t_param *params);
char			*add_precision_o(char *res, t_param *params);
char			*add_width(char *res, t_param *params);
void			add_width_pos(t_param *params, char *res, int len, int bufflen);
void			add_width_neg(t_param *params, char *res, int len, int bufflen);
char			*ft_itoa_x(unsigned int n);
char			*ft_itoa_xx(unsigned int n);
char			*ft_itoa_u(unsigned int i);
char			*ft_itoa_p(long n);
#endif
