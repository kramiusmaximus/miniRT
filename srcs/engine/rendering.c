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
			rvars.vec[0] = canvas_to_coords(h / vars->af, v / vars->af, &vars->scene);
			rvars.vec[1] = v_subtract(rvars.vec[0], ((t_camera *)vars->scene.camera->content)->coordinates);
			rvars.ray = make_ray(((t_camera *)vars->scene.camera->content)->coordinates, rvars.vec[1]);
			rvars.color = trace_ray(&rvars.ray, &vars->scene, N_PASSES, 1);
			for (int y_pixel = (int)(v * rvars.mult[0]); y_pixel < (int)((double)(v + 1) * rvars.mult[0]); y_pixel++)
				for (int x_pixel = (int)(h * rvars.mult[1]); x_pixel < (int)((double)(h + 1) * rvars.mult[1]); x_pixel++)
					put_pixel(&vars->mlx.image, x_pixel, y_pixel, rvars.color);
		}
	}
	return (0);
}

int render(t_vars *vars)
{
	clock_t t;

	t = clock();
	vars->scene.adjustment_factor = 1;
	move_camera(vars);
	if (is_moving(&vars->nav))
	{
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
	printf("%d\n", t);
	usleep(max(50000 - t, 0));
	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.win, vars->mlx.image.img, 0, 0);
	return (0);
}
