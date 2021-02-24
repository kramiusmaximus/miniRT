#include "miniRT.h"



static int render_image_bmp(t_vars *vars)
{
	t_render	rvars;

	rvars.mult[0] = ((double)vars->mlx.window_dims.height / (double)vars->scene.res.height) / vars->af;
	rvars.mult[1] = ((double)vars->mlx.window_dims.width / (double)vars->scene.res.width) / vars->af;
	for (int v = 0; v < (int)(((double)vars->scene.res.height) * vars->af); v++) //
	{
		for (int h = 0; h < (int)(((double)vars->scene.res.width) * vars->af); h++)
		{
			rvars.vec[0] = screen_to_world(h, v, vars);
			rvars.vec[1] = v_subtract(rvars.vec[0], ((t_camera *)vars->scene.camera->content)->coord);
			rvars.ray = make_ray(((t_camera *)vars->scene.camera->content)->coord, rvars.vec[1]);
			rvars.color = trace_ray(&rvars.ray, &vars->scene, N_PASSES, 1);
			for (int y_pixel = (int)(v * rvars.mult[0]); y_pixel < (int)((double)(v + 1) * rvars.mult[0]); y_pixel++)
				for (int x_pixel = (int)(h * rvars.mult[1]); x_pixel < (int)((double)(h + 1) * rvars.mult[1]); x_pixel++)
					put_pixel(vars->bmpim.image, x_pixel, y_pixel, rvars.color, vars->bmpim.header.width_px *  vars->bmpim.header.bits_per_pixel / 8, vars->mlx.image.bits_per_pixel);
		}
	}
	return (0);
}

int	make_bmp(t_vars *vars)
{
	int fd;

	if ((fd = open("./render.bmp", O_WRONLY)) < 0)
		error(NULL, &vars->scene);
	render_image_bmp(vars);
	return (0);
}
