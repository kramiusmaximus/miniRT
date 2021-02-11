#include "miniRT.h"

t_v	v_add(t_v v1, t_v v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return (v1);
}

t_v	v_subtract(t_v v1, t_v v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return (v1);
}

double		v_dot(t_v v1, t_v v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double		v_norm(t_v v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

t_v 	v_scalar_mult(t_v v, double s)
{
	v.x *= s;
	v.y *= s;
	v.z *= s;
	return (v);
}

t_v 	v_normalize(t_v v)
{
	return (v_scalar_mult(v, 1 / v_norm(v)));
}


int			solve_quadratic(double a, double b, double c, double t[2])
{
	double discriminant;

	discriminant = pow(b,2) - 4 * a * c;
	if (discriminant * 100000 == 0)
	{
		t[0] = -b / (2 * a);
		return (1);
	}
	else if (discriminant < 0)
		return (0);
	else
	{
		t[0] = (-b + sqrt(discriminant)) / (2 * a);
		t[1] = (-b - sqrt(discriminant)) / (2 * a);
		return (2);
	}
}

t_v v_cross(t_v v1, t_v v2)
{
	t_v	res;

	res.x = v1.y * v2.z - v1.z * v2.y;
	res.y = v1.z * v2.x - v1.x * v2.z;
	res.z = v1.x * v2.y - v1.y * v2.x;
	return (res);
}

t_v v_random(t_v v, double amount)
{
	double sign = rand() / 10000000;

	sign = sign > 100 ? 1 : -1;
	v.x += sign*random() / amount;
	v.y += sign*random() / amount;
	v.z += sign*random() / amount;

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

int max(int a, int b)
{
	return (a > b ? a : b);
}

int min(int a, int b)
{
	return (a < b ? a : b);
}

int abs(int a)
{
	return (a < 0 ? -a : a);
}