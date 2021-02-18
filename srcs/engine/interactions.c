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
	{
		if ((vars->scene.camera = vars->scene.camera->prev) != vars->scene.camera->prev)
			vars->rendered = 0;
	}
	else if (key == 124)
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

	nav = vars->nav;
	camera = vars->scene.camera->content;
	dirs = abs(nav.fwd_back) + abs(nav.lft_rght) + abs(nav.up_dwn);
	d = pow(STEP_SIZE, (double)1 / dirs);
	if (is_moving(&nav))
	{
		camera->coord.v[0] += d * nav.lft_rght;
		camera->coord.v[1] += d * nav.up_dwn;
		camera->coord.v[2] += d * nav.fwd_back;
	}
	return (0);
}

int is_moving(t_nav *nav)
{
	if (nav->fwd_back || nav->lft_rght || nav->up_dwn)
		return (1);
	return (0);
}
