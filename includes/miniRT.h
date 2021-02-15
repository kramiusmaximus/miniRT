#ifndef MINIRT_H
# define MINIRT_H
# include "objects.h"
# include "visual.h"
# include "vectors.h"
# include "interactions.h"
# include "tracing.h"
# include <math.h>
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include "../libft/includes/libft.h"
# define MAX_DIST		1000000000
# define BG_COLOR		0x00050505
# define NUM_THREADS 	1
# define N_PASSES		1
# define EPS			0.00000000001

typedef struct  	s_mlx
{
	void        	*mlx;
	void        	*win;
	t_image 		image;
}               	t_mlx;

typedef struct 		s_nav
{
	int 			fwd_back;
	int 			lft_rght;
	int 			up_dwn;
}					t_nav;

typedef struct 		s_vars
{
	t_mlx			*mlx;
	t_scene			*scene;
	int 			rendered;
	double 			af;
	t_nav			nav;
}					t_vars;

typedef struct 		s_tvars
{
	t_vars			*vars;
	int 			tid;
}					t_tvars;

typedef struct 		s_render
{
	t_vars			*vars;
	int 			tid;
	t_scene			*scene;
	t_v 			vec[2];
	double 			mult[2];
	int 			color;
	t_ray			ray;
}					t_render;


int 				move_camera(t_vars *vars);
int 				button_press(int key, t_vars *vars);
int					button_release(int key, t_vars *vars);
int					is_moving(t_nav *nav);
int 				put_pixel(t_image *image, int x, int y, int color);
int 				render(t_vars *vars);
int 				render_multi(t_vars *vars);

#endif
