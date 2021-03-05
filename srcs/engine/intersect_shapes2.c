#include "miniRT.h"

static int ray_intersect_sausage(t_ray *ray, t_object *cy_obj, t_t *t)
{
	t_ray_inter stuff;
	t_cy 		*cy;

	if (!ray || !cy_obj || !t)
		return (1);
	cy = &cy_obj->item.cy;
	stuff.i = 0;
	stuff.d[0] = v_dot(v_cross(ray->dir, cy->norm), v_cross(ray->dir, cy->norm));
	stuff.d[1] = 2 * v_dot(v_cross(ray->dir, cy->norm), v_cross(ray->origin, cy->norm));
	stuff.d[2] = -2 * v_dot(v_cross(ray->dir, cy->norm), v_cross(cy->coord, cy->norm));
	stuff.d[4] = v_dot(v_cross(cy->coord, cy->norm), v_cross(cy->coord, cy->norm));
	stuff.d[5] = v_dot(v_cross(ray->origin, cy->norm), v_cross(ray->origin, cy->norm));
	stuff.d[6] = -2 * v_dot(v_cross(ray->origin, cy->norm), v_cross(cy->coord, cy->norm)) - pow(cy->diameter / 2, 2);
	solve_quadratic(stuff.d[0], stuff.d[1] + stuff.d[2], stuff.d[4] + stuff.d[5] + stuff.d[6], t);
	stuff.i = t->size;
	while (stuff.i > 0)
	{
		stuff.v[0] = v_add(ray->origin, v_scalar_mult(ray->dir, t->arr[stuff.i - 1]));
		stuff.v[1] = v_subtract(stuff.v[0], cy->coord);
		if (v_dot(stuff.v[1], cy->norm) > cy->height || v_dot(stuff.v[1], cy->norm) < 0)
			t->arr[stuff.i - 1] = MAX_DIST;
		stuff.i--;
	}
	selection_sort(t->arr, t->size);
	return (0);
}

static int ray_intersect_caps(t_ray *ray, t_object *cy_obj, t_t *t)
{
	t_cy	*cy;
	t_ray_inter stuff;

	if (!ray || !cy_obj || !t)
		return (1);
	cy = &cy_obj->item.cy;
	stuff.d[0] = v_dot(cy->norm, v_subtract(cy->coord, ray->origin));
	stuff.d[1] = v_dot(cy->norm, ray->dir);
	if (!isinf(stuff.d[2] = stuff.d[0] / stuff.d[1]))
	{
		stuff.v[0] = v_add(ray->origin, v_scalar_mult(ray->dir, stuff.d[2]));
		stuff.v[1] = v_subtract(stuff.v[0], cy->coord);
		if (v_norm(stuff.v[1]) <= cy->diameter / 2)
			t->arr[t->size++] = stuff.d[2];
	}
	stuff.d[0] = v_dot(cy->norm, v_subtract(v_add(cy->coord, v_scalar_mult(cy->norm, cy->height-0.01)),\
	ray->origin));
	stuff.d[1] = v_dot(cy->norm, ray->dir);
	if (!isinf(stuff.d[2] = stuff.d[0] / stuff.d[1]))
	{
		stuff.v[0] = v_add(ray->origin, v_scalar_mult(ray->dir, stuff.d[2]));
		stuff.v[1] = v_subtract(stuff.v[0], v_add(cy->coord, v_scalar_mult(cy->norm, cy->height)));
		if (v_norm(stuff.v[1]) <= cy->diameter / 2)
			t->arr[t->size++] = stuff.d[2];
	}
	return (0);
}

int			ray_intersect_cy(t_ray *ray, t_object *cy_obj, t_t *t)
{
	if (!ray || ray_intersect_sausage(ray, cy_obj, t) ||
		ray_intersect_caps(ray, cy_obj, t))
		return (1);

	return (0);
}
