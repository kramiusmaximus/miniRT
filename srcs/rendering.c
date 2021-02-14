#include "miniRT.h"

extern 		t_vars vars;

void 		*render_section(void *arg)
{
	int 		id = (int)arg;
	t_scene 	*scene = vars.scene;
	t_mlx 		*mlx = vars.mlx;
	t_v 	c_coords;
	t_v 	r_dir;
	t_camera 	*cam = scene->camera;
	int 		color;
	double 		y_mult = ((double)scene->window_dims.height / (double)scene->res.height) / scene->adjustment_factor;
	double 		x_mult = ((double)scene->window_dims.width / (double)scene->res.width) / scene->adjustment_factor;
	int			section_h = scene->res.height * scene->adjustment_factor / NUM_THREADS ;
	double		r_rays = 1;
	t_ray 		ray;

	//printf("id: %d\n", id);
	for (int y_pixel = section_h * id; y_pixel < section_h * (id + 1); y_pixel++) //
	{
		for (int x_pixel = 0; x_pixel < scene->res.width * scene->adjustment_factor; x_pixel++)
		{
			c_coords = canvas_to_coords(x_pixel, y_pixel, scene);
			r_dir = v_subtract(c_coords, cam->coordinates);
			ray.dir = r_dir;
			ray.origin = c_coords;
			color = trace_ray(&ray, scene, N_PASSES);
			for (int y = (int)(y_pixel * y_mult); y < (y_pixel + 1) * y_mult; y++)
			{
				for (int x = (int)(x_pixel * x_mult); x < (x_pixel + 1) * x_mult; x++)
				{
					put_pixel(&mlx->image, x, y, color);
				}
			}
		}
	}
	pthread_exit(NULL);
}

int render_image()
{
	clock_t		start_t = clock();
	pthread_t	threads[NUM_THREADS];
	t_scene		*scene = vars.scene;
	t_mlx		*mlx = vars.mlx;
	double 		adjust_factor;
	double 		current_render_time;

	vars.scene->adjustment_factor = 1;
	move_camera(&vars);
	if (is_moving(&vars.nav))
	{
		vars.scene->parked = 0;
		vars.scene->adjustment_factor = 0.15;
		for (int tid = 0; tid < NUM_THREADS; tid++)
			pthread_create(&threads[tid], NULL, render_section, (void *)tid);
		for (int tid = 0; tid < NUM_THREADS; tid++)
			pthread_join(threads[tid], NULL);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->image.img, 0, 0);
	}
	else if (!vars.scene->parked)
	{
		vars.scene->parked = 1;
		for (int tid = 0; tid < NUM_THREADS; tid++)
			pthread_create(&threads[tid], NULL, render_section, (void *)tid);
		for (int tid = 0; tid < NUM_THREADS; tid++)
			pthread_join(threads[tid], NULL);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->image.img, 0, 0);
	}
	clock_t		end_t = clock();
	//printf("%d\n", (end_t - start_t)/100);
	return (0);
}