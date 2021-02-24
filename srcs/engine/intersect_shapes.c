#include "miniRT.h"

int			ray_intersect_sphere(t_ray *ray, t_object *sp_obj, t_t *t)
{
	double		coeff[3];
	t_sp		*sp;

	if (!ray || !sp_obj || !t)
		return (1);
	sp = &sp_obj->item.sp;
	coeff[0] = v_dot(ray->dir, ray->dir);
	coeff[1] = 2 * v_dot(v_subtract(ray->origin, sp->coord), ray->dir);
	coeff[2] = v_dot(v_subtract(ray->origin, sp->coord), v_subtract(ray->origin, sp->coord)) - pow(sp->diameter / 2, 2);
	solve_quadratic(coeff[0], coeff[1], coeff[2], t);
	return (0);
}

int 	ray_intersect_plane(t_ray	*ray, t_object *pl_obj, t_t *t)
{
	double 	nominator;
	double 	denominator;
	double 	res;
	t_pl	*pl;

	if (!ray || !pl_obj || !t)
		return (1);
	pl = &pl_obj->item.pl;
	nominator = v_dot(pl->norm, v_subtract(pl->coord, ray->origin));
	denominator = v_dot(pl->norm, ray->dir);
	if (!isinf(res = nominator / denominator))
	{
		t->size = 1;
		t->arr[0] = res;
	}
	return (0);
}

int ray_intersect_sq(t_ray *ray, t_object *sq_obj, t_t *t)
{
	double 	nominator;
	double 	denominator;
	double 	res;
	t_v 	p_contact;
	t_v 	v_contact;
	double 	a[2];
	double 	len;
	t_sq	*sq;

	if (!ray || !sq_obj || !t)
		return (1);
	sq = &sq_obj->item.sq;  // i dont think i even need a union sttucture here tbh
	nominator = v_dot(sq->norm, v_subtract(sq->coord, ray->origin));
	denominator = v_dot(sq->norm, ray->dir);
	if (!isinf(res = nominator / denominator))
	{
		p_contact = v_add(ray->origin, v_scalar_mult(ray->dir, res));
		v_contact = v_subtract(p_contact, sq->coord);

		a[0] = v_dot(v_contact, get_component(sq->basis, 2));
		a[1] = v_dot(v_contact, v_normalize(v_cross(get_component(sq->basis, 2), sq->norm)));
		len = sq->side_len / 2;
		if (a[0] < len && a[0] > -len && a[1] < len && a[1] > -len)
		{
			t->size = 1;
			t->arr[0] = res;
		}
	}
	return (0);
}

static int ray_intersect_sausage(t_ray *ray, t_object *cy_obj, t_t *t)
{
	t_cy 	*cy;
	double 	a[8];
	t_v p_contact;
	t_v op;
	int 	i;


	if (!ray || !cy_obj || !t)
		return (1);
	cy = &cy_obj->item.cy;
	a[0] = v_dot(v_cross(ray->dir, cy->norm), v_cross(ray->dir, cy->norm));
	a[1] = 2 * v_dot(v_cross(ray->dir, cy->norm), v_cross(ray->origin, cy->norm));
	a[2] = -2 * v_dot(v_cross(ray->dir, cy->norm), v_cross(cy->coord, cy->norm));
	a[3] = a[1] + a[2];
	a[4] = v_dot(v_cross(cy->coord, cy->norm), v_cross(cy->coord, cy->norm));
	a[5] = v_dot(v_cross(ray->origin, cy->norm), v_cross(ray->origin, cy->norm));
	a[6] = -2 * v_dot(v_cross(ray->origin, cy->norm), v_cross(cy->coord, cy->norm)) - pow(cy->diameter / 2, 2);
	a[7] = a[4] + a[5] + a[6];
	solve_quadratic(a[0], a[3], a[7], t);
	i = t->size;
	while (i > 0)
	{
		p_contact = v_add(ray->origin, v_scalar_mult(ray->dir, t->arr[i - 1]));
		op = v_subtract(p_contact, cy->coord);
		if (v_dot(op, cy->norm) > cy->height || v_dot(op, cy->norm) < 0)
		{
			t->arr[i - 1] = MAX_DIST;
		}
		i--;							// need to decrease t array size indrementally
	}
	selection_sort(t->arr, t->size);

	return (0);
}

static int ray_intersect_caps(t_ray *ray, t_object *cy_obj, t_t *t)
{
	t_cy	*cy;
	double nominator;
	double denominator;
	double res;
	t_v p_contact;
	t_v v_contact;

	if (!ray || !cy_obj || !t)
		return (1);
	cy = &cy_obj->item.cy;
	nominator = v_dot(cy->norm, v_subtract(cy->coord, ray->origin));
	denominator = v_dot(cy->norm, ray->dir);
	if (!isinf(res = nominator / denominator))
	{
		p_contact = v_add(ray->origin, v_scalar_mult(ray->dir, res));
		v_contact = v_subtract(p_contact, cy->coord);
		if (v_norm(v_contact) <= cy->diameter / 2)
			t->arr[t->size++] = res;
	}
	nominator = v_dot(cy->norm, v_subtract(v_add(cy->coord, v_scalar_mult(cy->norm, cy->height)),\
	ray->origin));
	denominator = v_dot(cy->norm, ray->dir);
	if (!isinf(res = nominator / denominator))
	{
		p_contact = v_add(ray->origin, v_scalar_mult(ray->dir, res));
		v_contact = v_subtract(p_contact, v_add(cy->coord, v_scalar_mult(cy->norm, cy->height)));
		if (v_norm(v_contact) <= cy->diameter / 2)
			t->arr[t->size++] = res;
	}
	return (0);
}

int			ray_intersect_cy(t_ray *ray, t_object *cy_obj, t_t *t)
{
	int 	sausage_hit;
	int 	caps_hit;

	if (!ray || ray_intersect_sausage(ray, cy_obj, t) ||
		ray_intersect_caps(ray, cy_obj, t))
		return (1);

	return (0);
}

int 		ray_intersect_tr(t_ray *ray, t_object *tr_obj, t_t *t)
{
	t_v 		v[7];
	t_tr 		*tr;
	t_object 	pl_obj;
	double		a;

	tr = &tr_obj->item.tr;
	v[0] = v_subtract(tr->p[1], tr->p[0]);
	v[1] = v_subtract(tr->p[2], tr->p[1]);
	v[2] = v_subtract(tr->p[0], tr->p[2]);
	pl_obj.item.pl.norm = v_cross(v[1], v[0]);
	pl_obj.item.pl.coord = tr->p[0];
	ray_intersect_plane(ray, &pl_obj, t);
	if (t->size)
	{
		v[3] = v_add(ray->origin, v_scalar_mult(ray->dir, t->arr[0])); // intersection point
		for (int i = 0; i < 3; i++)
		{
			v[4] = v_normalize(v_subtract(tr->p[(i + 1) % 3], tr->p[i]));
			v[5] = v_normalize(v_subtract(tr->p[(i + 2) % 3], tr->p[i]));
			v[6] = v_normalize(v_subtract(v[3], tr->p[i]));
			a = v_dot(v[4], v[5]);
			if (v_dot(v[6], v[4]) < a || v_dot(v[6], v[5]) < a)
				t->size = 0;
		}
	}
	return (0);
}