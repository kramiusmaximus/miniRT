#include "miniRT.h"

static int render_image(t_vars *vars)
{
	t_render	rvars;
	int			h;
	int 		v;

	rvars.vars = vars;
	rvars.mult[0] = 1 / vars->af;
	rvars.mult[1] = 1 / vars->af;
	v = 0;
	while (v < (int)(((double)vars->scene.res.height) * vars->af)) //
	{
		h = 0;
		while (h < (int)(((double)vars->scene.res.width) * vars->af))
		{
			rvars.vec[0] = screen_to_world(h, v, vars);
			rvars.vec[1] = v_subtract(rvars.vec[0], ((t_camera *)vars->scene.camera->content)->coord);
			rvars.ray = make_ray(((t_camera *) vars->scene.camera->content)->coord, rvars.vec[1], 0);
			rvars.color = trace_color(&rvars.ray, &vars->scene, N_PASSES, 1, MAX_DIST);
			fill_square(&rvars, v, h);
			h++;
		}
		v++;
	}
	return (0);
}

int render_mlx(t_vars *vars)
{
	mlx_hook(vars->mlx.win, 2, 1L << 2, (int (*)())key_press_hook, vars);
	mlx_hook(vars->mlx.win, 3, 1L << 3, (int (*)())key_release_hook, vars);
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
	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.win, vars->mlx.image.img, 0, 0);
	return (0);
}
