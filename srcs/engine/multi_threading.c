#include "miniRT.h"

static void 		*render_section(void *arg)
{
	t_render 	rvars;
	int			section_h;

	rvars.vars = ((t_tvars *)arg)->vars;
	rvars.tid = ((t_tvars *)arg)->tid;
	rvars.mult[0] = ((double)rvars.scene->window_dims.height / (double)rvars.scene->res.height) / rvars.vars->af;
	rvars.mult[1] = ((double)rvars.scene->window_dims.width / (double)rvars.scene->res.width) / rvars.vars->af;
	section_h = rvars.scene->res.height * rvars.vars->af / NUM_THREADS;
	for (int v = section_h * rvars.tid; v < section_h * (rvars.tid + 1); v++) //
	{
		for (int h = 0; h < rvars.scene->res.width * rvars.vars->af; h++)
		{
			rvars.vec[0] = canvas_to_coords(h / rvars.vars->af, v / rvars.vars->af, rvars.scene);
			rvars.vec[1] = v_subtract(rvars.vec[0], rvars.scene->camera->coordinates);
			rvars.ray = make_ray(rvars.vec[0], rvars.vec[1]);
			rvars.color = trace_ray(&rvars.ray, rvars.scene, N_PASSES, 1);
			for (int y_pixel = (int)(v * rvars.mult[0]); y_pixel < (int)((double)(v + 1) * rvars.mult[0]); y_pixel++)
				for (int x_pixel = (int)(h * rvars.mult[1]); x_pixel < (int)((double)(h + 1) * rvars.mult[1]); x_pixel++)
					put_pixel(&rvars.vars->mlx.image, x_pixel, y_pixel, rvars.color);
		}
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
