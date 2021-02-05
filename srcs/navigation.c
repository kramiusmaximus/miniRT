#include "miniRT.h"

int move_camera(int key, t_vars *vars)
{
	if (key == 13)
	{
		vars->scene->camera->coordinates.z += 2;
	}
	else if (key == 0)
	{
		vars->scene->camera->coordinates.x -= 2;
	}
	else if (key == 1)
	{
		vars->scene->camera->coordinates.z -= 2;
	}
	else if (key == 2)
	{
		vars->scene->camera->coordinates.x += 2;
	}
	else if (key == 3)
	{
		vars->scene->camera->coordinates.y += 2;
	}
	else if (key == 5)
	{
		vars->scene->camera->coordinates.y -= 2;
	}
	printf("%d\n", key);
	return (0);
}
