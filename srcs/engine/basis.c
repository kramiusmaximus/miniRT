#include "miniRT.h"

t_v 		transform(t_v	v, t_camera *cam)
{
	v = v_mat_mul_vec(m_transpose(cam->basis), v);
	v = v_add(v, cam->coord);
	return (v);
}

t_v			screen_to_world(int h, int v, t_vars *vars)
{
	t_camera 	*cam;
	t_v 		c;
	double 		square_width;

	cam = vars->scene.camera->content;
	square_width = 2 * tan(cam->fov / 2 * M_PI / 180) / vars->scene.res.width;
	c.v[0] = (h - (vars->scene.res.width * vars->af / 2)) * square_width;
	c.v[1] = -(v - (vars->scene.res.height * vars->af / 2)) * square_width;
	c.v[2] = vars->af;
	c = transform(c, cam);
	return (c);
}
