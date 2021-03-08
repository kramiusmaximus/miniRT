/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handling2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:18:51 by pfelipa           #+#    #+#             */
/*   Updated: 2021/03/08 17:18:52 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			move_camera(t_vars *vars)
{
	t_nav		nav;
	t_camera	*camera;
	double		d;
	int			dirs;
	t_v			disp;

	nav = vars->nav;
	camera = vars->scene.camera->content;
	if (is_rotating(&vars->nav))
		camera->rot_mat = rotate_xyz(nav.rot_up_dwn * 0.1,\
		-nav.rot_lft_rght * 0.1, 0, camera->rot_mat);
	if (is_moving(&vars->nav))
	{
		dirs = abs(nav.fwd_back) + abs(nav.lft_rght) + abs(nav.up_dwn);
		d = pow(STEP_SIZE, (double)1 / dirs);
		disp = v_make(d * nav.lft_rght, d * nav.up_dwn, d * nav.fwd_back);
		camera->coord = v_add(camera->coord,\
		v_mat_mul_vec(m_transpose(camera->rot_mat), disp));
	}
	return (0);
}

int			is_moving(t_nav *nav)
{
	if (nav->fwd_back || nav->lft_rght || nav->up_dwn)
		return (1);
	return (0);
}

int			is_rotating(t_nav *nav)
{
	if (nav->rot_lft_rght || nav->rot_up_dwn)
		return (1);
	return (0);
}
