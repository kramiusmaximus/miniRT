#include "miniRT.h"

t_3dvec	vector_add(t_3dvec v1, t_3dvec v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return (v1);
}

t_3dvec	vector_subtract(t_3dvec v1, t_3dvec v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return (v1);
}

double		vector_dot(t_3dvec v1, t_3dvec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double		vector_norm(t_3dvec v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

t_3dvec 	vector_scalar_mult(t_3dvec v, double s)
{
	v.x *= s;
	v.y *= s;
	v.z *= s;
	return (v);
}

t_3dvec 	vector_normalize(t_3dvec v)
{
	return (vector_scalar_mult(v, 1/vector_norm(v)));
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