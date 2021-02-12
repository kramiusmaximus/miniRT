#include "miniRT.h"

int button_press(int key, t_vars *vars)
{
	// navigation controls
	if (key == 13)
		vars->nav.fwd_back = 1;
	if (key == 1)
		vars->nav.fwd_back = -1;
	if (key == 0)
		vars->nav.lft_rght = -1;
	if (key == 2)
		vars->nav.lft_rght = 1;
	if (key == 3)
		vars->nav.up_dwn = 1;
	if (key == 5)
		vars->nav.up_dwn = -1;
	//printf("%d\n", key);
}

int button_release(int key, t_vars *vars)
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

int move_camera(t_vars *vars)
{
	t_nav nav = vars->nav;
	t_camera *camera = vars->scene->camera;
	double d = 5;

	if (nav.fwd_back && nav.lft_rght)
	{
		d /= sqrt(2);
		camera->coordinates.z += d * nav.fwd_back;
		camera->coordinates.x += d * nav.lft_rght;
	}
	else if (nav.lft_rght)
		camera->coordinates.x += d * nav.lft_rght;
	else if (nav.fwd_back)
		camera->coordinates.z += d * nav.fwd_back;
	if (nav.up_dwn)
		camera->coordinates.y += d * nav.up_dwn;
	return (0);
}

int is_moving(t_nav *nav)
{
	if (nav->fwd_back || nav->lft_rght || nav->up_dwn)
		return (1);
	return (0);
}
