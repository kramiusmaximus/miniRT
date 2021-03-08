#include "minirt.h"

static void 		*render_section(void *arg)
{
	t_render 	rvars;
	int 		h;
	int 		v;
	int			section_h;
	int 		rem;

	rem = 0;
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
	int 		tid;

	tid = 0;
	while (tid < NUM_THREADS)
	{
		tvars[tid].tid = tid;
		tvars[tid].vars = vars;
		pthread_create(&threads[tid], NULL, render_section, (void *)&tvars[tid]);
		tid++;
	}
	tid = 0;
	while (tid < NUM_THREADS)
		pthread_join(threads[tid++], NULL);
	return (0);
}
