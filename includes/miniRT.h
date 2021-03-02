#ifndef MINIRT_H
# define MINIRT_H
# include "objects.h"
# include "color.h"
# include "maths.h"
# include "event_handling.h"
# include "tracing.h"
# include "parser.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/errno.h>
# include "main_structs.h"
# include "libft.h"
# include "mlx.h"
# include "bitmap.h"
# define MAX_DIST		1000000000
# define BG_COLOR		0xDAFFFC
# define NUM_THREADS 	4
# define N_PASSES		5
# define EPS			0.0000001
# define AF				0.15
# define STEP_SIZE		5
# define WINDOW_HEIGHT  1280
# define WINDOW_WIDTH   1980


int 				put_pixel(void *img, int x, int y, int color, int line_len, int bpp);
int 				render_mlx(t_vars *vars);
int 				render_multi(t_vars *vars);
void 				error(char *msg, t_scene *scene);
void				ft_lstcclear(t_listc **lst);
void 				free_mem(t_scene *scene);


#endif
