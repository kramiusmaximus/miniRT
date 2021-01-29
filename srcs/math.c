#include "miniRT.h"

t_vector	vector_add(t_vector v1, t_vector v2)
{
	t_vector res;

	if (v1.count != v2.count || v1.count > 100 || v2.count > 100)
	{
		printf("v1 and/or v2 have improper dimensions.\n", v1.count, v2.count);
		return (res);
	}
	res.count = v1.count;
	while (v1.count > 0)
	{
		res.arr[v1.count - 1] = v1.arr[v1.count - 1] + v2.arr[v1.count - 1];
		v1.count--;
	}
	return (res);
}

t_vector	vector_subtract(t_vector v1, t_vector v2)
{
	t_vector res;

	if (v1.count != v2.count || v1.count > 100 || v2.count > 100)
	{
		printf("v1 and/or v2 have improper dimensions.\n", v1.count, v2.count);
		return (res);
	}
	res.count = v1.count;
	while (v1.count > 0)
	{
		res.arr[v1.count - 1] = v1.arr[v1.count - 1] - v2.arr[v1.count - 1];
		v1.count--;
	}
	return (res);
}

double		vector_dot(t_vector v1, t_vector v2)
{
	double	res;

	res = 0;
	if (v1.count != v2.count || v1.count > 100 || v2.count > 100)
	{
		printf("v1 and/or v2 have improper dimensions.\n", v1.count, v2.count);
		return (res);
	}
	while (v1.count > 0)
	{
		res += v1.arr[v1.count - 1] * v2.arr[v1.count - 1];
		v1.count--;
	}
	return (res);
}