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
	return (vector_scalar_mult(v, vector_norm(v)));
}