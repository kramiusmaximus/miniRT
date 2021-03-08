/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:13:13 by pfelipa           #+#    #+#             */
/*   Updated: 2021/03/08 17:13:14 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	norminette_cancer1(int key, t_vars *vars)
{
	if (key == 53)
		exit_hook(vars);
	else if (key == 11)
		screen_shot(vars);
}

void		key_press_hook1(int key, t_vars *vars)
{
	if (key == 13)
		vars->nav.fwd_back = 1;
	else if (key == 1)
		vars->nav.fwd_back = -1;
	else if (key == 0)
		vars->nav.lft_rght = -1;
	else if (key == 2)
		vars->nav.lft_rght = 1;
	else if (key == 49)
		vars->nav.up_dwn = 1;
	else if (key == 14)
		vars->nav.up_dwn = -1;
	else if (key == 123)
		vars->nav.rot_lft_rght = -1;
	else if (key == 124)
		vars->nav.rot_lft_rght = 1;
	else if (key == 126)
		vars->nav.rot_up_dwn = 1;
	else if (key == 125)
		vars->nav.rot_up_dwn = -1;
	else if (key == 45)
		switch_camera(1, vars);
	else if (key == 46)
		switch_camera(-1, vars);
	norminette_cancer1(key, vars);
}

void		key_release_hook(int key, t_vars *vars)
{
	if (key == 13 && vars->nav.fwd_back == 1)
		vars->nav.fwd_back = 0;
	if (key == 1 && vars->nav.fwd_back == -1)
		vars->nav.fwd_back = 0;
	if (key == 0 && vars->nav.lft_rght == -1)
		vars->nav.lft_rght = 0;
	if (key == 2 && vars->nav.lft_rght == 1)
		vars->nav.lft_rght = 0;
	if (key == 49 && vars->nav.up_dwn == 1)
		vars->nav.up_dwn = 0;
	if (key == 14 && vars->nav.up_dwn == -1)
		vars->nav.up_dwn = 0;
	if (key == 123 && vars->nav.rot_lft_rght == -1)
		vars->nav.rot_lft_rght = 0;
	if (key == 124 && vars->nav.rot_lft_rght == 1)
		vars->nav.rot_lft_rght = 0;
	if (key == 126 && vars->nav.rot_up_dwn == 1)
		vars->nav.rot_up_dwn = 0;
	if (key == 125 && vars->nav.rot_up_dwn == -1)
		vars->nav.rot_up_dwn = 0;
}

int			exit_hook(t_vars *vars)
{
	ft_printf("Quitting application...\n");
	free_mem(&vars->scene);
	exit(0);
}

void		switch_camera(int i, t_vars *vars)
{
	if (i && vars->scene.camera != vars->scene.camera->next)
	{
		if (i == 1)
			vars->scene.camera = vars->scene.camera->next;
		else
			vars->scene.camera = vars->scene.camera->prev;
		vars->full_res_rendered = 0;
	}
}
