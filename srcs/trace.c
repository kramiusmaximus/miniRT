#include <tcl.h>
#include "miniRT.h"

extern 		t_vars vars;
extern 		int **prev_frame;
double 		avg_render_t;


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

t_object	*ray_intersect_plane(t_3dvec p_origin, t_3dvec v_dir, t_object *pl_obj, double *t)
{
	double nominator;
	double denominator;
	double res;

	nominator = vector_dot(pl_obj->shape.pl.normal, vector_subtract(pl_obj->shape.pl.coordinates, p_origin));
	denominator = vector_dot(pl_obj->shape.pl.normal, v_dir);
	if ((res = nominator / denominator) > *t)
		return (NULL);
	*t = res;
	return (pl_obj);
}

t_object	*ray_intersect_sq(t_3dvec p_origin, t_3dvec v_dir, t_object *sq_object, double *t)
{
	double nominator;
	double denominator;
	double res;
	t_3dvec p_contact;
	t_3dvec v_contact;
	double a1;
	double a2;
	double len;

	nominator = vector_dot(sq_object->shape.sq.top, vector_subtract(sq_object->shape.sq.coordinates, p_origin));
	denominator = vector_dot(sq_object->shape.sq.top, v_dir);
	if (isinf(res = nominator / denominator))
		return (NULL);
	p_contact = vector_add(p_origin, vector_scalar_mult(v_dir, res));
	v_contact = vector_subtract(p_contact, sq_object->shape.sq.coordinates);
	a1 = vector_dot(v_contact, sq_object->shape.sq.front); // front and side vectors are assumed to be unit vectors
	a2 = vector_dot(v_contact, sq_object->shape.sq.side);
	len = sq_object->shape.sq.side_len / 2;
	if (a1 > len || a1 < -len || a2 > len || a2 < -len)
		return (NULL);
	*t = res;
	return (sq_object);
}

t_object	*ray_intersect_cy(t_3dvec p_origin, t_3dvec v_dir, t_object *cy_object, double *t)
{
	t_3dvec n;
	double	k;
	double 	a;
	double 	b;
	double 	c;
	int 	solution_n;

	n = cy_object->shape.cy.normal;
	k = vector_dot(n, vector_subtract())
	a = vector_dot(v_dir, v_dir);
	b = 2 * vector_dot(v_dir, p_origin - cy_object->shape.cy.coordinates - vector_scalar_mult());
	c = 0;
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
		n = obj->shape.pl.normal;
	else if (obj->type & SQ)
		n = obj->shape.sq.top;
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
	if (!closest_t || !scene) // why is this condition always false?
		return (NULL);
	p = scene->object;
	while (p)
	{
		if (p->type & SP)
			object_hit = ray_intersect_sphere(p_origin, v_dir, p, &t);
		else if (p->type & PL)
			object_hit = ray_intersect_plane(p_origin, v_dir, p, &t);
		else if (p->type & SQ)
			object_hit = ray_intersect_sq(p_origin, v_dir, p, &t);
		else if (p->type & CY)
			object_hit = ray_intersect_cy(p_origin, v_dir, p, &t);
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

int process_light(t_object *obj, t_3dvec contact_p, t_scene *scene, t_3dvec pixel_ray)
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
		if (!trace_result(contact_p, vector_subtract(p->coordinates, contact_p), &t, scene, 0.000000000001) && vector_dot(n, pixel_ray) < 0)
		{
			dot = vector_dot(n, l);
			dot = dot < 0 ? 0 : dot;
			light_effects = rgb_add(light_effects,rgb_multiply_scalar(p->color, dot * p->intensity));
		}
		p = p->next;
	}
	if (light_effects == 0)
	{}
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
		light_effects = process_light(object_hit, vector_add(origin, vector_scalar_mult(dir, closest_t)), scene, dir);
		//origin = vector_add(origin, vector_scalar_mult(dir, closest_t));
		//dir = surface_vector(object_hit, origin);
		return (rgb_multiply(color, light_effects));
		//return (rgb_add(rgb_multiply_scalar(color, (1 - object_hit->reflectivity)),rgb_multiply_scalar(, )));
	}
	return (0xE9DC65);
}

void 		*render_section(void *arg)
{
	int 		id = (int)arg;
	t_scene 	*scene = vars.scene;
	t_mlx 		*mlx = vars.mlx;
	t_3dvec 	c_coords;
	t_camera 	*cam = scene->camera;
	int 		color;
	double 		y_mult = ((double)scene->window_dims.height / (double)scene->res.height) / scene->adjustment_factor;
	double 		x_mult = ((double)scene->window_dims.width / (double)scene->res.width) / scene->adjustment_factor;
	int			section_h = scene->res.height * scene->adjustment_factor / NUM_THREADS ;

	//printf("id: %d\n", id);
	for (int y_pixel = section_h * id; y_pixel < section_h * (id + 1); y_pixel++) //
	{
		for (int x_pixel = 0; x_pixel < scene->res.width * scene->adjustment_factor; x_pixel++)
		{
			c_coords = canvas_to_coords(x_pixel, y_pixel, scene);
			color = trace_ray(cam->coordinates, vector_subtract(c_coords, cam->coordinates), scene);
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
		vars.scene->adjustment_factor = 0.3;
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