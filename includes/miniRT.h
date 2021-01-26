#ifndef MINIRT_MINIRT_H
# define MINIRT_MINIRT_H
# include <math.h>
# include <mlx.h>

typedef struct  s_data {
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
}               t_data;

#endif
