#include "miniRT.h"

static void 		*render_section(void *arg)
{
	t_render 	rvars;
	int 		h;
	int 		v;
	int			section_h;

	rvars.vars = ((t_tvars *)arg)->vars;
	rvars.tid = ((t_tvars *)arg)->tid;
	rvars.mult[0] = 1 / rvars.vars->af;
	rvars.mult[1] = 1 / rvars.vars->af;
	section_h = (int)((double)rvars.vars->scene.res.height * rvars.vars->af / NUM_THREADS);
	v = rvars.tid * section_h;
	while (v < (rvars.tid + 1) * section_h)
	{
		h = 0;
		while (h < rvars.vars->scene.res.width * rvars.vars->af)
		{
			rvars.vec[0] = screen_to_world(h, v, rvars.vars);
			rvars.vec[1] = v_subtract(rvars.vec[0], ((t_camera *)rvars.vars->scene.camera->content)->coord);
			rvars.ray = make_ray(((t_camera *)rvars.vars->scene.camera->content)->coord, rvars.vec[1], 0);
			rvars.color = trace_color(&rvars.ray, &rvars.vars->scene, N_PASSES, 1, MAX_DIST);
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
