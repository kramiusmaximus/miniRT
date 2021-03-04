#include "miniRT.h"

t_v screen_to_world(int h, int v, t_vars *vars, int aa)
{
	t_camera 	*cam;
	t_v 		c;
	double 		square_width;
	double 		rand_x;
	double 		rand_y;


	cam = vars->scene.camera->content;
	square_width = 2 * tan(cam->fov / 2 * M_PI / 180) / vars->scene.res.width;
	rand_x = aa ? (double)rand() / 5000000 * (square_width) : 0;
	rand_y = aa ? (double)rand() / 5000000 * (square_width) : 0;
	c.v[0] = (h - (vars->scene.res.width * vars->af / 2) + rand_x) * square_width;
	c.v[1] = -(v - (vars->scene.res.height * vars->af / 2) + rand_y) * square_width;
	c.v[2] = vars->af;
	c = v_mat_mul_vec(m_transpose(cam->rot_mat), c);
	c = v_add(c, cam->coord);
	return (c);
}