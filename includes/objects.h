#ifndef OBJECTS_H
# define OBJECTS_H
# include "vectors.h"
# define SP			0b00000001
# define PL			0b00000010
# define SQ			0b00000100
# define CY			0b00001000
# define TR			0b00010000

typedef struct		s_sp
{
	t_v				coord;
	double 			diameter;
}					t_sp;

typedef struct		s_pl
{
	t_v				coord;
	t_v 			norm;
}					t_pl;

typedef struct		s_sq
{
	t_v				coord;
	t_v 			norm;
	t_v				front;
	t_v 			side;
	double 			side_len;
}					t_sq;

typedef	struct		s_cy
{
	t_v				coord;
	t_v 			norm;
	double 			diameter;
	double 			height;
}					t_cy;

typedef struct 		s_tr
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
	int 			type;
	t_shape			item;
	double 			reflectivity;
	double 			transperancy;
	double 			refraction;
	int 			color;
}					t_object;

typedef struct		s_ambient
{
	double 			intensity;
	int 			color;
}					t_ambient;

typedef struct		s_light
{
	double			intensity;
	t_v				coordinates;
	int 			color;
}					t_light;

#endif
