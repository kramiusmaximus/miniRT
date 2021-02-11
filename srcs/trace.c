#include <tcl.h>
#include "miniRT.h"

extern 		t_vars vars;
extern 		int **prev_frame;
double 		avg_render_t;

/*
t_object	*ray_intersect_sphere(t_v p_origin, t_v v_dir, t_object *sphere_obj, double *t)
{
	double 	a;
	double 	b;
	double 	c;
	int 	solution_n;

	a = v_dot(v_dir, v_dir);
	b = 2 * v_dot(v_subtract(p_origin, sphere_obj->data.sp.coordinates), v_dir);
	c = v_dot(v_subtract(p_origin, sphere_obj->data.sp.coordinates),
			  v_subtract(p_origin, sphere_obj->data.sp.coordinates)) - pow(sphere_obj->data.sp.diameter / 2, 2);
	solution_n = solve_quadratic(a, b, c, t);
	if (solution_n)
		return (sphere_obj);
	return (NULL);
}
 */

int			solve_quadratic_new(double a, double b, double c, t_t *t)
{
	double discriminant;

	if (!t)
		return (1);
	discriminant = pow(b,2) - 4 * a * c;
	if (discriminant * 100000 == 0)
	{
		t->arr[0] = -b / (2 * a);
		t->size = 1;
	}
	else if (discriminant < 0)
		t->size = 0;
	else
	{
		t->arr[0] = (-b + sqrt(discriminant)) / (2 * a);
		t->arr[1] = (-b - sqrt(discriminant)) / (2 * a);
		t->size = 2;
	}
	return (0);
}

int			ray_intersect_sphere_new(t_ray *ray, t_object *sphere_obj, t_t *t)
{
	t_sp		sp;
	double		coeff[3];

	sp = sphere_obj->data.sp;
	coeff[0] = v_dot(ray->dir, ray->dir);
	coeff[1] = 2 * v_dot(v_subtract(ray->origin, sp.coordinates), ray->dir);
	coeff[2] = v_dot(v_subtract(ray->origin, sp.coordinates), v_subtract(ray->origin, sp.coordinates)) - pow(sp.diameter / 2, 2);
	solve_quadratic_new(coeff[0], coeff[1], coeff[2], t);
	return (0);
}







t_object	*ray_intersect_plane(t_v p_origin, t_v v_dir, t_object *pl_obj, double *t)
{
	double nominator;
	double denominator;
	double res;

	nominator = v_dot(pl_obj->data.pl.normal, v_subtract(pl_obj->data.pl.coordinates, p_origin));
	denominator = v_dot(pl_obj->data.pl.normal, v_dir);
	if (isinf(res = nominator / denominator))
		return (NULL);
	*t = res;
	return (pl_obj);
}

t_object	*ray_intersect_sq(t_v p_origin, t_v v_dir, t_object *sq_object, double *t)
{
	double nominator;
	double denominator;
	double res;
	t_v p_contact;
	t_v v_contact;
	double a1;
	double a2;
	double len;

	nominator = v_dot(sq_object->data.sq.top, v_subtract(sq_object->data.sq.coordinates, p_origin));
	denominator = v_dot(sq_object->data.sq.top, v_dir);
	if (isinf(res = nominator / denominator))
		return (NULL);
	p_contact = v_add(p_origin, v_scalar_mult(v_dir, res));
	v_contact = v_subtract(p_contact, sq_object->data.sq.coordinates);
	a1 = v_dot(v_contact, sq_object->data.sq.front); // front and side vectors are assumed to be unit vectors
	a2 = v_dot(v_contact, sq_object->data.sq.side);
	len = sq_object->data.sq.side_len / 2;
	if (a1 > len || a1 < -len || a2 > len || a2 < -len)
		return (NULL);
	*t = res;
	return (sq_object);
}

int 		ray_intersect_sausage(t_v p_origin, t_v v_dir, t_object *cy_object, double *t)
{
	t_cy 	cy = cy_object->data.cy;
	double 	a;
	double	b1;
	double	b2;
	double 	b;
	double	c1;
	double	c2;
	double 	c3;
	double 	c;
	double 	theta;
	int 	solution_n;
	t_v p_contact;
	t_v op;
	int 	i;


	a = v_dot(v_cross(v_dir, cy.normal), v_cross(v_dir, cy.normal));
	b1 = 2 * v_dot(v_cross(v_dir, cy.normal), v_cross(p_origin, cy.normal));
	b2 = -2 * v_dot(v_cross(v_dir, cy.normal), v_cross(cy.coordinates, cy.normal));
	b = b1 + b2;
	c1 = v_dot(v_cross(cy.coordinates, cy.normal), v_cross(cy.coordinates, cy.normal));
	c2 = v_dot(v_cross(p_origin, cy.normal), v_cross(p_origin, cy.normal));
	c3 = -2 * v_dot(v_cross(p_origin, cy.normal), v_cross(cy.coordinates, cy.normal)) - pow(cy.diameter / 2, 2);
	c = c1 + c2 + c3;
	solution_n = solve_quadratic(a, b, c, t);
	if (solution_n)
	{
		i = solution_n;
		while (i > 0)
		{
			p_contact = v_add(p_origin, v_scalar_mult(v_dir, t[i - 1]));
			op = v_subtract(p_contact, cy.coordinates);
			if (v_dot(op, cy.normal) > cy.height || v_dot(op, cy.normal) < 0)
			{
				t[i - 1] = MAX_DIST;
				solution_n--;
			}
			i--;
		}
	}
	return (solution_n);
}

int ray_intersect_caps(t_v p_origin, t_v v_dir, t_object *cy_object, double *t, int solution_n)
{
	t_cy	cy;
	double nominator;
	double denominator;
	double res;
	t_v p_contact;
	t_v v_contact;

	// repeat this process for the top cap cause this is just the bottom cap rn
	solution_n = 0;
	cy = cy_object->data.cy;
	// top cap;
	nominator = v_dot(cy.normal, v_subtract(cy.coordinates, p_origin));
	denominator = v_dot(cy.normal, v_dir);
	if (!isinf(res = nominator / denominator))
	{
		p_contact = v_add(p_origin, v_scalar_mult(v_dir, res));
		v_contact = v_subtract(p_contact, cy.coordinates);
		if (v_norm(v_contact) <= cy.diameter / 2)
			t[solution_n++] = res;
	}
	nominator = v_dot(cy.normal,
					  v_subtract(v_add(cy.coordinates, v_scalar_mult(cy.normal, cy.height)), p_origin));
	denominator = v_dot(cy.normal, v_dir);
	if (!isinf(res = nominator / denominator))
	{
		p_contact = v_add(p_origin, v_scalar_mult(v_dir, res));
		v_contact = v_subtract(p_contact, v_add(cy.coordinates, v_scalar_mult(cy.normal, cy.height)));
		if (v_norm(v_contact) <= cy.diameter / 2)
			t[solution_n++] = res;
	}
	return (solution_n);
}

t_object	*ray_intersect_cy(t_v p_origin, t_v v_dir, t_object *cy_object, double *t)
{
	t_cy 	cy = cy_object->data.cy;
	int 	sausage_hit;
	int 	caps_hit;

	sausage_hit = ray_intersect_sausage(p_origin, v_dir, cy_object, t);
	caps_hit = ray_intersect_caps(p_origin, v_dir, cy_object, t, sausage_hit);
	if (caps_hit || sausage_hit)
		return (cy_object);
	return (NULL);
}







/*
t_v 	surface_vector(t_object *obj, t_v p_contact)
{
	t_v n = {0, 0, 0};
	t_cy	cy;
	double 	d;

	if (obj->type & SP)
		n = v_normalize(v_subtract(p_contact, obj->data.sp.coordinates));
	else if (obj->type & PL)
		n = obj->data.pl.normal;
	else if (obj->type & SQ)
		n = obj->data.sq.top;
	else if (obj->type & CY)
	{
		cy = obj->data.cy;
		d = point_line_dist(cy.coordinates, v_add(cy.coordinates, v_scalar_mult(cy.normal, cy.height)), p_contact);
		if (d < cy.diameter / 2 - 0.0001)
			n = cy.normal;
		else
		{}
	}
	else if (obj->type & TR)
	{}
	return (n);
}
 */

t_v surface_vector_new(t_ray *ray, t_object *obj, t_intersect *inter)
{
	t_v n = {0, 0, 0};
	t_cy	cy;
	double 	d;

	// what if we're inside?
	if (obj->type & SP)
		n = v_normalize(v_subtract(ray->origin, obj->data.sp.coordinates));
	else if (obj->type & PL)
		n = obj->data.pl.normal;
	else if (obj->type & SQ)
		n = obj->data.sq.top;
	else if (obj->type & CY)
	{
		cy = obj->data.cy;
		d = point_line_dist(cy.coordinates, v_add(cy.coordinates, v_scalar_mult(cy.normal, cy.height)), inter->contact);
		if (d < cy.diameter / 2 - 0.0001)
			n = cy.normal;
	}
	else if (obj->type & TR)
	{}
	return (n);
}







/*
t_object 	*trace_result(t_v p_origin, t_v v_dir, double *closest_t, t_scene *scene, double d)
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
 */

t_intersect *trace_result_new(t_ray *ray, t_scene *scene, double d)
{
	t_object	*obj;
	t_object	*obj_closest;
	t_t 		t;
	int 		i;

	t.closest = MAX_DIST;
	if (!ray || !scene)
		return (NULL);
	obj = scene->object;
	while (obj)
	{
		t.size = 0;
		if (obj->type & SP)
			ray_intersect_sphere_new(ray, obj, &t);
		else if (obj->type & PL)
		{}//inter = ray_intersect_plane_new(ray, obj);
		else if (obj->type & SQ)
		{}//inter = ray_intersect_sq_new(ray, obj);
		else if (obj->type & CY)
		{}//inter = ray_intersect_cy_new(ray, obj);
		else if (obj->type & TR)
		{}
		i = 0;
		while (i < t.size)
		{
			if (t.arr[i] > d && t.arr[i] < t.closest)
			{
				t.closest = t.arr[i];
				obj_closest = obj;
			}
			i++;
		}
		obj = obj->next;
	}
	ray->intersect = process_t(ray, obj_closest, &t);
	return (ray->intersect);
}

/*
int process_light(t_object *obj, t_v contact_p, t_scene *scene, t_v pixel_ray)
{
	int 	light_effects;
	int 	p_effect;
	t_v l;
	t_v n;
	double 	t;
	t_light *p;
	double 	dot;

	light_effects = rgb_multiply_scalar(scene->ambient.color, scene->ambient.intensity);
	p = scene->light;
	n = surface_vector(obj, contact_p);
	while (p)
	{
		t = 1;
		l = v_normalize(v_subtract(p->coordinates, contact_p));
		if (!trace_result(contact_p, v_subtract(p->coordinates, contact_p), &t, scene, 0.000000000001) &&
				v_dot(n, pixel_ray) < 0)
		{
			dot = v_dot(n, l);
			dot = dot < 0 ? 0 : dot;
			p_effect = rgb_multiply_scalar(rgb_multiply_scalar(p->color, dot * p->intensity),100000 / pow(v_norm(
					v_subtract(p->coordinates, contact_p)), 2));
			light_effects = rgb_add(light_effects, p_effect);
		}
		p = p->next;
	}
	return (light_effects);
}
*/

int process_light_new(t_ray *ray, t_scene *scene)
{
	int 	light_effects;
	int 	p_effect;
	t_v l;
	t_v n;
	double 	t;
	t_light *p;
	t_intersect	*inter;
	t_ray 	ray_l;
	double 	dot;

	inter = ray->intersect;
	light_effects = rgb_multiply_scalar(scene->ambient.color, scene->ambient.intensity);
	p = scene->light;
	n = inter->surface_v;
	while (p)
	{
		t = 1;
		l = v_normalize(v_subtract(p->coordinates, inter->contact));
		ray_l = make_ray(inter->contact, p->coordinates);
		if (!trace_result_new(&ray_l, scene, 0.000000001) &&
			v_dot(n, ray->dir) < 0)  /// actually incorrect but works for now
		{
			dot = v_dot(n, l);
			dot = dot < 0 ? 0 : dot;
			p_effect = rgb_multiply_scalar(rgb_multiply_scalar(p->color, dot * p->intensity),100000 / pow(v_norm(
					v_subtract(p->coordinates, inter->contact)), 2));
			light_effects = rgb_add(light_effects, p_effect);
		}
		p = p->next;
	}
	return (light_effects);
}






/*

int 		trace_ray(t_v origin, t_v dir, t_scene	*scene)
{
	double		closest_t;
	t_object	*object_hit;
	int			color;
	int 		light_effects;
	int 		counter;
	t_v 	normal;
	t_object	*next;

	closest_t = MAX_DIST;
	counter = 0;
	if ((object_hit = trace_result(origin, dir, &closest_t, scene, 1)))
	{
		color = object_hit->color;
		light_effects = process_light(object_hit, v_add(origin, v_scalar_mult(dir, closest_t)), scene, dir);
		//origin = v_add(origin, v_scalar_mult(dir, closest_t));
		//dir = surface_vector(object_hit, origin);
		return (rgb_multiply(color, light_effects));
		//return (rgb_add(rgb_multiply_scalar(color, (1 - object_hit->reflectivity)),rgb_multiply_scalar(, )));
	}
	return (0xE9DC65);
}
*/

int 		trace_ray_new(t_ray	*ray, t_scene *scene)
{
	t_intersect int_p;
	double 		closest_t;
	t_intersect *inter;
	int 		color;
	int 		light_effects;

	if ((inter = trace_result_new(ray, scene, 1)))
	{
		color = inter->obj->color;
		light_effects = process_light_new(ray, scene);
		//origin = v_add(origin, v_scalar_mult(dir, closest_t));
		//dir = surface_vector(inter, origin);
		return (rgb_multiply(color, light_effects));
		//return (rgb_add(rgb_multiply_scalar(color, (1 - inter->reflectivity)),rgb_multiply_scalar(, )));
	}
	return (0xE9DC65);
}







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
			color = trace_ray_new(&ray, scene);
			///color = trace_ray(cam->coordinates, r_dir, scene);
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
		vars.scene->adjustment_factor = 0.2;
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