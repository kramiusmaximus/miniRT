#include "miniRT.h"

int key_press_hook(int key, t_vars *vars)
{
	// navigation controls
	if (key == 13)
		vars->nav.fwd_back = 1;
	else if (key == 1)
		vars->nav.fwd_back = -1;
	else if (key == 0)
		vars->nav.lft_rght = -1;
	else if (key == 2)
		vars->nav.lft_rght = 1;
	else if (key == 3)
		vars->nav.up_dwn = 1;
	else if (key == 5)
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
	{
		if ((vars->scene.camera = vars->scene.camera->prev) != vars->scene.camera->prev)
			vars->rendered = 0;
	}
	else if (key == 46)
	{
		if ((vars->scene.camera = vars->scene.camera->next) != vars->scene.camera->next)
			vars->rendered = 0;
	}
	else if (key == 53)
		exit_hook(vars);
	printf("%d\n", key);
}

int key_release_hook(int key, t_vars *vars)
{
	// navigation controls
	if (key == 13 && vars->nav.fwd_back == 1)
		vars->nav.fwd_back = 0;
	if (key == 1 && vars->nav.fwd_back == -1)
		vars->nav.fwd_back = 0;
	if (key == 0 && vars->nav.lft_rght == -1)
		vars->nav.lft_rght = 0;
	if (key == 2 && vars->nav.lft_rght == 1)
		vars->nav.lft_rght = 0;
	if (key == 3 && vars->nav.up_dwn == 1)
		vars->nav.up_dwn = 0;
	if (key == 5 && vars->nav.up_dwn == -1)
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

int exit_hook(t_vars *vars)
{
	ft_printf("Quitting application...\n");
	exit(0);
}

int move_camera(t_vars *vars)
{
	t_nav 		nav;
	t_camera 	*camera;
	double 		d;
	int 		dirs;
	t_m 		b;
	t_v 		disp;

	nav = vars->nav;
	camera = vars->scene.camera->content;

	/// change basis of camera to initial basis (remove rotation and displacement effects (wb canvaas centering
	/// and protrusion?))

	/// rotate camera
	if (is_rotating(&vars->nav))
	{
		if (nav.rot_lft_rght)
			camera->basis = v_mat_mul(camera->basis, rotate_y(nav.rot_lft_rght * 0.1));
		if (nav.rot_up_dwn)
			camera->basis = v_mat_mul(camera->basis, rotate_x(nav.rot_up_dwn * 0.1));
	}

	/// move camera

	if (is_moving(&vars->nav))
	{
		dirs = abs(nav.fwd_back) + abs(nav.lft_rght) + abs(nav.up_dwn);
		d = pow(STEP_SIZE, (double)1 / dirs);
		disp = v_make(d * nav.lft_rght, d * nav.up_dwn, d * nav.fwd_back);
		camera->coord = v_add(camera->coord, v_mat_mul_vec(camera->basis, disp));
	}


	return (0);
}

int is_moving(t_nav *nav)
{
	if (nav->fwd_back || nav->lft_rght || nav->up_dwn)
		return (1);
	return (0);
}

int is_rotating(t_nav *nav)
{
	if (nav->rot_lft_rght || nav->rot_up_dwn)
		return (1);
	return (0);
}
