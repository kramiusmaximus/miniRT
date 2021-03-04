#include "miniRT.h"

int 				fetch_pixel_color(int v, int h, t_vars *vars)
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

static void 		*render_section(void *arg)
{
	t_render 	rvars;
	int 		h;
	int 		v;
	int			section_h;
	int 		c[AA_SAMPLE_NUM];
	int 		rem = 0;

	rvars.vars = ((t_tvars *)arg)->vars;
	rvars.tid = ((t_tvars *)arg)->tid;
	rvars.mult[0] = 1 / rvars.vars->af;
	rvars.mult[1] = 1 / rvars.vars->af;
	section_h = (int)((double)rvars.vars->scene.res.height * rvars.vars->af / NUM_THREADS);
	if (rvars.tid == NUM_THREADS - 1 && !rvars.vars->full_res_rendered)
		rem = (int)((double)rvars.vars->scene.res.height * rvars.vars->af) % section_h;
	v = rvars.tid * section_h;
	while (v < (rvars.tid + 1) * section_h + rem)
	{
		h = 0;
		while (h < rvars.vars->scene.res.width * rvars.vars->af)
		{
			rvars.color = fetch_pixel_color(v, h, rvars.vars);
			/*
			if (!rvars.vars->full_res_rendered || AA_SAMPLE_NUM < 2)
			{
				rvars.vec[0] = screen_to_world(h, v, rvars.vars, 0);
				rvars.vec[1] = v_subtract(rvars.vec[0], ((t_camera *)rvars.vars->scene.camera->content)->coord);
				rvars.ray = make_ray(((t_camera *)rvars.vars->scene.camera->content)->coord, rvars.vec[1], 0);
				c[0] = trace_color(&rvars.ray, &rvars.vars->scene, N_PASSES, 1, MAX_DIST);
				rvars.color = c[0];
			}
			else
			{
				for (int i = 0; i < AA_SAMPLE_NUM; i++)
				{
					rvars.vec[0] = screen_to_world(h, v, rvars.vars, 1);
					rvars.vec[1] = v_subtract(rvars.vec[0], ((t_camera *)rvars.vars->scene.camera->content)->coord);
					rvars.ray = make_ray(((t_camera *)rvars.vars->scene.camera->content)->coord, rvars.vec[1], 0);
					c[i] = trace_color(&rvars.ray, &rvars.vars->scene, N_PASSES, 1, MAX_DIST);
				}
				rvars.color = rgb_avg(c, AA_SAMPLE_NUM);
			}
			 */
			fill_square(&rvars, v, h);
			h++;
		}
		v++;
	}
	pthread_exit(NULL);
}

int render_multi(t_vars *vars)
{
	t_tvars		tvars[NUM_THREADS];
	pthread_t 	threads[NUM_THREADS];

	for (int tid = 0; tid < NUM_THREADS; tid++)
	{
		tvars[tid].tid = tid;
		tvars[tid].vars = vars;
		pthread_create(&threads[tid], NULL, render_section, (void *)&tvars[tid]);
	}
	for (int tid = 0; tid < NUM_THREADS; tid++)
		pthread_join(threads[tid], NULL);
	return (0);
}
