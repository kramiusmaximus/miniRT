#ifndef MINIRT_H
# define MINIRT_H
# include "objects.h"
# include "color.h"
# include "maths.h"
# include "event_handling.h"
# include "tracing.h"
# include "parser.h"
# include <math.h>
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/errno.h>
# include "main_structs.h"
# include "../libft/includes/libft.h"
# include "bitmap.h"
# define MAX_DIST		1000000000
# define BG_COLOR		0
# define NUM_THREADS 	4
# define N_PASSES		15
# define EPS			0.00000000001
# define AF				0.15
# define STEP_SIZE		4
# define WINDOW_HEIGHT 720
# define WINDOW_WIDTH  1280

int put_pixel(void *img, int x, int y, int color, int line_len, int bpp);
int 				render_mlx(t_vars *vars);
int 				render_multi(t_vars *vars);
int					make_bmprender_bmp(t_vars *vars);
int 				error(char *msg, t_scene *scene);


#endif
