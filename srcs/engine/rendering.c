#include "miniRT.h"

int 			fetch_pixel_color(int v, int h, t_vars *vars)
{
	t_v 	o;
	t_v 	dir;
	t_ray 	ray;
	int 	c[AA_SAMPLE_NUM];

	if (!vars->full_res_rendered || AA_SAMPLE_NUM < 2)
	{
		o = screen_to_world(h, v, vars, 0);
		dir = v_subtract(o, ((t_camera *)vars->scene.camera->content)->coord);
		ray = make_ray(((t_camera *)vars->scene.camera->content)->coord, dir, 0);
		c[0] = trace_color(&ray, &vars->scene, N_PASSES, 1, MAX_DIST);
		return (c[0]);
	}
	else
	{
		for (int i = 0; i < AA_SAMPLE_NUM; i++)
		{
			o = screen_to_world(h, v, vars, 1);
			dir = v_subtract(o, ((t_camera *)vars->scene.camera->content)->coord);
			ray = make_ray(((t_camera *)vars->scene.camera->content)->coord, dir, 0);
			c[i] = trace_color(&ray, &vars->scene, N_PASSES, 1, MAX_DIST);
		}
		return(rgb_avg(c, AA_SAMPLE_NUM));
	}
}

static int 	render_image(t_vars *vars)
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
			rvars.color = fetch_pixel_color(v, h, vars);
			fill_square(&rvars, v, h);
			h++;
		}
		v++;
	}
	return (0);
}

int 		render_mlx(t_vars *vars)
{
	mlx_hook(vars->mlx.win, 2, 1L << 2, (int (*)()) key_press_hook1, vars);
	mlx_hook(vars->mlx.win, 3, 1L << 3, (int (*)())key_release_hook, vars);
	if (is_moving(&vars->nav) || is_rotating(&vars->nav))
	{
		move_camera(vars);
		vars->full_res_rendered = 0;
		vars->af = AF;
	}
	else if (!vars->full_res_rendered)
	{
		vars->full_res_rendered = 1;
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
