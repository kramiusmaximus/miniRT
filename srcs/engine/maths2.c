#include "miniRT.h"


t_v 	v_scalar_mult(t_v v, double s)
{
	v.v[0] *= s;
	v.v[1] *= s;
	v.v[2] *= s;
	return (v);
}

t_v 	v_normalize(t_v v)
{
	return (v_scalar_mult(v, 1 / v_norm(v)));
}

t_v v_cross(t_v v1, t_v v2)
{
	t_v	res;

	res.v[0] = v1.v[1] * v2.v[2] - v1.v[2] * v2.v[1];
	res.v[1] = v1.v[2] * v2.v[0] - v1.v[0] * v2.v[2];
	res.v[2] = v1.v[0] * v2.v[1] - v1.v[1] * v2.v[0];
	return (res);
}

t_v v_random(t_v v, double amount)
{
	double sign = rand() / 10000000;

	sign = sign > 100 ? 1 : -1;
	v.v[0] += sign*random() / amount;
	v.v[1] += sign*random() / amount;
	v.v[2] += sign*random() / amount;

	return (v);
}

double point_line_dist(t_v x0, t_v x1, t_v p)
{
	double nom;
	double denom;

	nom = v_norm(v_cross(v_subtract(p, x0), v_subtract(p, x1)));
	denom = v_norm(v_subtract(x1, x0));

	return (nom / denom);
}
