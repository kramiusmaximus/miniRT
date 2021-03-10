/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 15:51:07 by pfelipa           #+#    #+#             */
/*   Updated: 2021/03/08 15:51:10 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "objects.h"
# include "color.h"
# include "maths1.h"
# include "event_handling1.h"
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
# include "../mlx/mlx.h"
# include "bitmap.h"
# define MAX_DIST		1000000000
# define BG_COLOR		0xB5FFF7
# define THRDS 			1
# define N_PASSES		10
# define EPS			0.00000001
# define AF				0.15
# define STEP_SIZE		5
# define WINDOW_HEIGHT  720
# define WINDOW_WIDTH   1280
# define AA_SAMPLE_NUM  1

void				fill_square(t_render *rvars, int v, int h);
void				put_pixel(t_render *rvars, int x, int y, int bpp);
int					render_mlx(t_vars *vars);
int					render_multi(t_vars *vars);
void				error(char *msg, t_scene *scene);
void				ft_lstcclear(t_listc **lst);
void				free_mem(t_scene *scene);
void				free_split(char **split);

#endif
