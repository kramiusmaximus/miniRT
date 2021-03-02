#include "miniRT.h"

static int render_image(t_vars *vars)
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
			rvars.ray = make_ray(((t_camera *) vars->scene.camera->content)->coord, rvars.vec[1], 0);
			rvars.color = trace_color(&rvars.ray, &vars->scene, N_PASSES, 1, MAX_DIST);
			for (int y_pixel = (int)(v * rvars.mult[0]); y_pixel < (int)((double)(v + 1) * rvars.mult[0]); y_pixel++)
				for (int x_pixel = (int)(h * rvars.mult[1]); x_pixel < (int)((double)(h + 1) * rvars.mult[1]); x_pixel++)
					put_pixel(vars->mlx.image.addr, x_pixel, y_pixel, rvars.color, vars->mlx.image.line_length, vars->mlx.image.bits_per_pixel);
		}
	}
	return (0);
}

int render_mlx(t_vars *vars)
{
	clock_t t;

	t = clock();
	if (is_moving(&vars->nav) || is_rotating(&vars->nav))
	{
		move_camera(vars);
		vars->rendered = 0;
		vars->af = AF;
	}
	else if (!vars->rendered)
	{
		vars->rendered = 1;
		vars->af = 1;
	}
	else
		return (0);
	if (NUM_THREADS > 1)
		render_multi(vars);
	else
		render_image(vars);
	t = clock() - t;
	usleep(max(40000 - t, 0));
	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.win, vars->mlx.image.img, 0, 0);
	return (0);
}
