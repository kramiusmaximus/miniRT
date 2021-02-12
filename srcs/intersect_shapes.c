#include "miniRT.h"

int			ray_intersect_sphere(t_ray *ray, t_object *sphere_obj, t_t *t)
{
	t_sp		sp;
	double		coeff[3];

	if (!ray || !sphere_obj || !t)
		return (1);
	sp = sphere_obj->data.sp;
	coeff[0] = v_dot(ray->dir, ray->dir);
	coeff[1] = 2 * v_dot(v_subtract(ray->origin, sp.coordinates), ray->dir);
	coeff[2] = v_dot(v_subtract(ray->origin, sp.coordinates), v_subtract(ray->origin, sp.coordinates)) - pow(sp.diameter / 2, 2);
	solve_quadratic(coeff[0], coeff[1], coeff[2], t);
	return (0);
}

int 	ray_intersect_plane(t_ray	*ray, t_object *pl_obj, t_t *t)
{
	double nominator;
	double denominator;
	double res;

	if (!ray || !pl_obj || !t)
		return (1);
	nominator = v_dot(pl_obj->data.pl.normal, v_subtract(pl_obj->data.pl.coordinates, ray->origin));
	denominator = v_dot(pl_obj->data.pl.normal, ray->dir);
	if (!isinf(res = nominator / denominator))
	{
		t->size = 1;
		t->arr[0] = res;
	}
	return (0);
}

int ray_intersect_sq(t_ray *ray, t_object *sq_object, t_t *t)
{
	double nominator;
	double denominator;
	double res;
	t_v p_contact;
	t_v v_contact;
	double a[2];
	double len;

	if (!ray || !sq_object || !t)
		return (1);
	nominator = v_dot(sq_object->data.sq.top, v_subtract(sq_object->data.sq.coordinates, ray->origin));
	denominator = v_dot(sq_object->data.sq.top, ray->dir);
	if (!isinf(res = nominator / denominator))
	{
		p_contact = v_add(ray->origin, v_scalar_mult(ray->dir, res));
		v_contact = v_subtract(p_contact, sq_object->data.sq.coordinates);
		a[0] = v_dot(v_contact, sq_object->data.sq.front); // front and side vectors are assumed to be unit vectors
		a[1] = v_dot(v_contact, sq_object->data.sq.side);
		len = sq_object->data.sq.side_len / 2;
		if (a[0] < len && a[0] > -len && a[1] < len && a[1] > -len)
		{
			t->size = 1;
			t->arr[0] = res;
		}
	}
	return (0);
}

static int ray_intersect_sausage(t_ray *ray, t_object *cy_object, double *t)
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


	a = v_dot(v_cross(ray->dir, cy.normal), v_cross(ray->dir, cy.normal));
	b1 = 2 * v_dot(v_cross(ray->dir, cy.normal), v_cross(ray->dir, cy.normal));
	b2 = -2 * v_dot(v_cross(ray->dir, cy.normal), v_cross(cy.coordinates, cy.normal));
	b = b1 + b2;
	c1 = v_dot(v_cross(cy.coordinates, cy.normal), v_cross(cy.coordinates, cy.normal));
	c2 = v_dot(v_cross(ray->dir, cy.normal), v_cross(ray->dir, cy.normal));
	c3 = -2 * v_dot(v_cross(ray->origin, cy.normal), v_cross(cy.coordinates, cy.normal)) - pow(cy.diameter / 2, 2);
	c = c1 + c2 + c3;
	solution_n = solve_quadratic(a, b, c, t);
	if (solution_n)
	{
		i = solution_n;
		while (i > 0)
		{
			p_contact = v_add(ray->origin, v_scalar_mult(ray->dir, t[i - 1]));
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

static int ray_intersect_caps(t_ray *ray, t_object *cy_object, t_t *t)
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

int 		ray_intersect_cy(t_ray *ray, t_object *cy_object, t_t *t)
{
	t_cy 	cy = cy_object->data.cy;
	int 	sausage_hit;
	int 	caps_hit;

	if (!ray || ray_intersect_sausage(ray, cy_object, t) ||
		ray_intersect_caps(ray, cy_object, t))
		return (1);
	return (0);
}