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
# define BG_COLOR		0x00070712
# define NUM_THREADS 	3
# define N_PASSES		3
# define EPS			0.00000000001
# define AF				0.3
# define STEP_SIZE		3

int 				put_pixel(t_image *image, int x, int y, int color);
int 				render(t_vars *vars);
int 				render_multi(t_vars *vars);
int 				error(char *msg);

#endif
