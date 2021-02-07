#include "miniRT.h"

extern 		t_vars vars;
extern 		int **prev_frame;
double 		avg_render_t;
int 		d = 0;


t_object	*ray_intersect_sphere(t_3dvec p_origin, t_3dvec v_dir, t_object *sphere_obj, double *t)
{
	double 	a;
	double 	b;
	double 	c;
	int 	solution_n;

	a = vector_dot(v_dir, v_dir);
	b = 2 * vector_dot(vector_subtract(p_origin, sphere_obj->shape.sp.coordinates), v_dir);
	c = vector_dot(vector_subtract(p_origin, sphere_obj->shape.sp.coordinates),vector_subtract(p_origin, sphere_obj->shape.sp.coordinates)) - pow(sphere_obj->shape.sp.diameter / 2, 2);
	solution_n = solve_quadratic(a, b, c, t);
	if (solution_n)
		return (sphere_obj);
	return (NULL);
}
t_3dvec 	surface_vector(t_object *obj, t_3dvec p_contact)
{
	t_3dvec n = {0,0,0};

	if (obj->type & SP)
		n = vector_normalize(vector_subtract(p_contact, obj->shape.sp.coordinates));
	else if (obj->type & PL)
	{}
	else if (obj->type & SQ)
	{}
	else if (obj->type & CY)
	{}
	else if (obj->type & TR)
	{}
	return (n);
}

t_object 	*trace_result(t_3dvec p_origin, t_3dvec v_dir, double *closest_t, t_scene *scene, double d)
{
	t_object	*object_hit_closest;
	t_object	*object_hit;
	double 		t[] = {*closest_t, *closest_t};
	t_object	*p;

	object_hit_closest = NULL;
	if (!closest_t || !scene)
		return (NULL);
	p = scene->object;
	while (p)
	{
		if (p->type & SP)
			object_hit = ray_intersect_sphere(p_origin, v_dir, p, &t);
		else if (p->type & PL)
		{}
		else if (p->type & SQ)
		{}
		else if (p->type & CY)
		{}
		else if (p->type & TR)
		{}
		if (t[0] > d && t[0] < *closest_t)
		{
			*closest_t = t[0];
			object_hit_closest = object_hit;
		}
		if (t[1] > d && t[1] < *closest_t)
		{
			*closest_t = t[1];
			object_hit_closest = object_hit;
		}
		p = p->next;
	}
	return (object_hit_closest);
}

int 		process_light(t_object *obj, t_3dvec contact_p, t_scene *scene)
{
	int 	light_effects;
	t_3dvec l;
	t_3dvec n;
	double 	t;
	t_light *p;
	double 	dot;

	light_effects = rgb_multiply_scalar(scene->ambient.color, scene->ambient.intensity);
	p = scene->light;
	n = surface_vector(obj, contact_p);
	while (p)
	{
		t = 1;
		l = vector_normalize(vector_subtract(p->coordinates, contact_p));
		if (!trace_result(contact_p, vector_subtract(p->coordinates, contact_p), &t, scene, 0.000000000001))
		{
			dot = vector_dot(n, l);
			dot = dot < 0 ? 0 : dot;
			light_effects = rgb_add(light_effects,rgb_multiply_scalar(p->color, dot * p->intensity));
		}
		p = p->next;
	}
	return (light_effects);
}

int 		trace_ray(t_3dvec origin, t_3dvec dir, t_scene	*scene)
{
	double		closest_t;
	t_object	*object_hit;
	int			color;
	int 		light_effects;
	int 		counter;
	t_3dvec 	normal;
	t_object	*next;

	closest_t = MAX_DIST;
	counter = 0;
	if ((object_hit = trace_result(origin, dir, &closest_t, scene, 1)))
	{
		color = object_hit->color;
		light_effects = process_light(object_hit, vector_add(origin, vector_scalar_mult(dir, closest_t)), scene);
		//origin = vector_add(origin, vector_scalar_mult(dir, closest_t));
		//dir = surface_vector(object_hit, origin);
		return (rgb_multiply(color, light_effects));
		//return (rgb_add(rgb_multiply_scalar(color, (1 - object_hit->reflectivity)),rgb_multiply_scalar(, )));
	}
	return (0);
}

void 		*render_section(void *arg)
{
	int 		id = (int)arg;
	t_scene 	*scene = vars.scene;
	t_mlx 		*mlx = vars.mlx;
	t_3dvec 	c_coords;
	t_camera 	*cam = scene->camera;
	int 		color;
	double 		y_mult = 1 / ((double)scene->window_dims.height / (double)scene->res.height);
	double 		x_mult = 1 / ((double)scene->window_dims.width / (double)scene->res.width);
	int			section_h = scene->window_dims.height / NUM_THREADS;
	int 		n_diff_pixels = 0;

	for (int y_box = section_h * id; y_box < section_h * (id + 1); y_box++) //
	{
		for (int x_box = 0; x_box < scene->res.width; x_box++)
		{
			c_coords = canvas_to_coords(x_box + 0.5, y_box + 0.5, scene);
			color = trace_ray(cam->coordinates, vector_subtract(c_coords, cam->coordinates), scene);
			for (int y = (int) (y_box * y_mult); y < (y_box + 1) * y_mult; y++)
			{
				for (int x = (int) (x_box * x_mult + d); x < (x_box + 1) * x_mult; x++)
				{
					put_pixel(&mlx->image, x, y, color);
				}
			}
		}
	}
	//printf("%d\n", n_diff_pixels);
	pthread_exit(NULL);
}

int 		render_image(t_vars *vars)
{
	clock_t		start_t = clock();
	pthread_t	threads[NUM_THREADS];
	t_scene		*scene = vars->scene;
	t_mlx		*mlx = vars->mlx;
	double 		adjust_factor;
	double 		current_render_time;

	for (int tid = 0; tid < NUM_THREADS; tid++)
		pthread_create(&threads[tid], NULL, render_section, (void *)tid);
	for (int tid = 0; tid < NUM_THREADS; tid++)
		pthread_join(threads[tid], NULL);
	current_render_time = (double)(clock() - start_t);
	avg_render_t = (avg_render_t / 2 + current_render_time / 2) / 1000;
	adjust_factor =  1000 / (double)avg_render_t;
	adjust_factor = adjust_factor < 0.2 ? 0.2 : adjust_factor;
	adjust_factor = adjust_factor > 1 ? 1 : adjust_factor;
	printf("%f, ", avg_render_t);
	printf("%f\n", adjust_factor);
	scene->res.width = (int)((double)scene->res.width * adjust_factor);
	scene->res.height = (int)((double)scene->res.height * adjust_factor);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->image.img, 0, 0);
	return (0);
}