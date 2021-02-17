#ifndef MINIRT_H
# define MINIRT_H
# include "objects.h"
# include "visual.h"
# include "vectors.h"
# include "interactions.h"
# include "tracing.h"
# include "parser.h"
# include <math.h>
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <fcntl.h>
#include <sys/errno.h>
# include "main_structs.h"
# include "../libft/includes/libft.h"
# define MAX_DIST		1000000000
# define BG_COLOR		0x00101010
# define NUM_THREADS 	4
# define N_PASSES		4
# define EPS			0.00000000001

int 				put_pixel(t_image *image, int x, int y, int color);
int 				render(t_vars *vars);
int 				render_multi(t_vars *vars);
int 				error(char *msg);

#endif
