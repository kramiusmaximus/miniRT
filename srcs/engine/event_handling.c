#include "miniRT.h"

void key_press_hook(int key, t_vars *vars)
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
		switch_camera(-1,vars);
	else if (key == 53)
		exit_hook(vars);
	else if (key == 11)
		screen_shot(vars);
}

void key_release_hook(int key, t_vars *vars)
{
	if (key == 13 && vars->nav.fwd_back == 1)
		vars->nav.fwd_back = 0;
	if (key == 1 && vars->nav.fwd_back == -1)
		vars->nav.fwd_back = 0;
	if (key == 0 && vars->nav.lft_rght == -1)
		vars->nav.lft_rght = 0;
	if (key == 2 && vars->nav.lft_rght == 1)
		vars->nav.lft_rght = 0;
	/*if (key == 49 && vars->nav.up_dwn == 1)
		vars->nav.up_dwn = 0;
	if (key == 14 && vars->nav.up_dwn == -1)
		vars->nav.up_dwn = 0;*/
	if (key == 123 && vars->nav.rot_lft_rght == -1)
		vars->nav.rot_lft_rght = 0;
	if (key == 124 && vars->nav.rot_lft_rght == 1)
		vars->nav.rot_lft_rght = 0;
	if (key == 126 && vars->nav.rot_up_dwn == 1)
		vars->nav.rot_up_dwn = 0;
	if (key == 125 && vars->nav.rot_up_dwn == -1)
		vars->nav.rot_up_dwn = 0;
}

int exit_hook(t_vars *vars)
{
	ft_printf("Quitting application...\n");
	free_mem(&vars->scene);
	exit(0);
}

void switch_camera(int i, t_vars *vars)
{
	if (i || vars->scene.camera != vars->scene.camera->next)
	{
		if (i == 1)
			vars->scene.camera = vars->scene.camera->next;
		else
			vars->scene.camera = vars->scene.camera->prev;
		vars->rendered = 0;
	}
}

int move_camera(t_vars *vars)
{
	t_nav 		nav;
	t_camera 	*camera;
	double 		d;
	int 		dirs;
	t_v 		disp;

	nav = vars->nav;
	camera = vars->scene.camera->content;
	if (is_rotating(&vars->nav))
		camera->rot_mat = rotate_xyz(nav.rot_up_dwn * 0.1, -nav.rot_lft_rght * 0.1, 0, camera->rot_mat);
	if (is_moving(&vars->nav))
	{
		dirs = abs(nav.fwd_back) + abs(nav.lft_rght) + abs(nav.up_dwn);
		d = pow(STEP_SIZE, (double)1 / dirs);
		disp = v_make(d * nav.lft_rght, d * nav.up_dwn, d * nav.fwd_back);
		camera->coord = v_add(camera->coord, v_mat_mul_vec(m_transpose(camera->rot_mat), disp));
	}
	return (0);
}

int is_moving(t_nav *nav)
{
	if (nav->fwd_back || nav->lft_rght/* || nav->up_dwn*/)
		return (1);
	return (0);
}

int is_rotating(t_nav *nav)
{
	if (nav->rot_lft_rght || nav->rot_up_dwn)
		return (1);
	return (0);
}
