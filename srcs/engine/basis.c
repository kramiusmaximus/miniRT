/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:39:18 by pfelipa           #+#    #+#             */
/*   Updated: 2021/03/08 16:39:19 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_v	screen_to_world(int h, int v, t_vars *vars, int aa)
{
	t_cam		*cam;
	t_v			c;
	double		square_width;
	double		r[2];

	cam = vars->scene.camera->cntnt;
	square_width = 2 * tan(cam->fov / 2 * M_PI / 180) / vars->scene.res.width;
	r[0] = aa ? (double)rand() / 16000000 * (square_width) : 0;
	r[1] = aa ? (double)rand() / 16000000 * (square_width) : 0;
	c.v[0] = (-h + (vars->scene.res.width\
	* vars->af / 2) + r[0]) * square_width;
	c.v[1] = -(v - (vars->scene.res.ht * vars->af / 2)
			+ r[1]) * square_width;
	c.v[2] = vars->af;
	c = v_mat_mul_vec(cam->basis, c);
	c = v_add(c, cam->coord);
	return (c);
}
