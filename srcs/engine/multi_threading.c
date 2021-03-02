#include "miniRT.h"

static void 		*render_section(void *arg)
{
	t_render 	rvars;
	int			k[4];
	int			section_h;

	rvars.vars = ((t_tvars *)arg)->vars;
	rvars.tid = ((t_tvars *)arg)->tid;
	rvars.mult[0] = ((double)rvars.vars->mlx.window_dims.height / (double)rvars.vars->scene.res.height) / rvars.vars->af;
	rvars.mult[1] = ((double)rvars.vars->mlx.window_dims.width / (double)rvars.vars->scene.res.width) / rvars.vars->af;
	section_h = (int)((double)rvars.vars->scene.res.height * rvars.vars->af / NUM_THREADS);
	k[0] = rvars.tid * section_h;
	while (k[0] < (rvars.tid + 1) * section_h)
	{
		k[1] = 0;
		while (k[1] < rvars.vars->scene.res.width * rvars.vars->af)
		{
			rvars.vec[0] = screen_to_world(k[1], k[0], rvars.vars);
			rvars.vec[1] = v_subtract(rvars.vec[0], ((t_camera *)rvars.vars->scene.camera->content)->coord);
			rvars.ray = make_ray(((t_camera *) rvars.vars->scene.camera->content)->coord, rvars.vec[1], 0);
			rvars.color = trace_color(&rvars.ray, &rvars.vars->scene, N_PASSES, 1, MAX_DIST);
			k[2] = (int)(((double)k[0]) * rvars.mult[0]);
			while (k[2] < ((double)(k[0] + 1)) * rvars.mult[0])
			{
				k[3] = (int)((double)k[1] * rvars.mult[1]);
				while (k[3] < ((double)(k[1] + 1)) * rvars.mult[1])
				{
					put_pixel(rvars.vars->mlx.image.addr, k[3], k[2], rvars.color, rvars.vars->mlx.image.line_length,
							  32);
					k[3]++;
				}
				k[2]++;
			}
			k[1]++;
		}
		k[0]++;
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
