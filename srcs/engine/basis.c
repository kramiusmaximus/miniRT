#include "miniRT.h"

t_v 		transform(t_v	v, t_camera *cam)
{
	// rotate
	v = v_mat_mul_vec(cam->basis, v);
	// translate
	v = v_add(v, cam->coord);
	return (v);
}

t_v			screen_to_world(int h, int v, t_vars *vars)
{
	t_v 		initial_dir = {0,0,1};
	double 		rot[3];
	t_camera 	*cam= vars->scene.camera->content;
	t_v 		c;
	double 		square_width = 2 * tan(cam->fov / 2 * M_PI / 180) / vars->scene.res.width;

	// center the screen
	c.v[0] = (h - (vars->scene.res.width * vars->af / 2)) * square_width;
	c.v[1] = -(v - (vars->scene.res.height * vars->af / 2)) * square_width;
	c.v[2] = square_width * vars->scene.res.width * vars->af / (2 * tan(cam->fov / 2 * M_PI / 180));/// whats the reasoning behind this?

	c = transform(c, cam);
	return (c);
}

