#ifndef MINIRT_H
# define MINIRT_H
# include "objects.h"
# include "visual.h"
# include "vectors.h"
# include "scene.h"
# include "tracing.h"
# include <math.h>
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# define MAX_DIST	1000000000
# define BG_COLOR	0x00050505
# define NUM_THREADS 1
# define N_PASSES	2

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
	t_nav			nav;
}					t_vars;


int 				render_image();
int 				move_camera(t_vars *vars);
int 				button_press(int key, t_vars *vars);
int					button_release(int key, t_vars *vars);
int					is_moving(t_nav *nav);
int 				put_pixel(t_image *image, int x, int y, int color);

#endif
