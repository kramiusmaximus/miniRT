/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:01:45 by pfelipa           #+#    #+#             */
/*   Updated: 2021/03/08 16:01:47 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H
# include "maths1.h"
# define SP			0b00000001
# define PL			0b00000010
# define SQ			0b00000100
# define CY			0b00001000
# define TR			0b00010000

typedef struct		s_sp
{
	t_v				coord;
	double			diameter;
}					t_sp;

typedef struct		s_pl
{
	t_v				coord;
	t_v				norm;
}					t_pl;

typedef struct		s_sq
{
	t_v				coord;
	t_m				basis;
	t_v				norm;
	double			side_len;
}					t_sq;

typedef	struct		s_cy
{
	t_v				coord;
	t_v				norm;
	double			diameter;
	double			h;
}					t_cy;

typedef struct		s_tr
{
	t_v				p[3];
}					t_tr;

typedef union		u_shape
{
	t_sp			sp;
	t_pl			pl;
	t_sq			sq;
	t_cy			cy;
	t_tr			tr;
}					t_shape;

typedef struct		s_object
{
	int				type;
	t_shape			item;
	double			reflectivity;
	double			transperancy;
	double			refraction;
	int				color;
}					t_object;

typedef struct		s_ambient
{
	double			intensity;
	int				color;
}					t_ambient;

typedef struct		s_light
{
	double			intensity;
	t_v				coords;
	int				color;
}					t_light;

#endif
