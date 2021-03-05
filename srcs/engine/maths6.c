#include "miniRT.h"

t_v get_component(t_m mat, int col)
{
	t_v v;
	int i;

	i = 0;
	while (i < mat.size[0])
	{
		v.v[i] = mat.m[i][col];
		i++;
	}
	return (v);
}

t_v v_mid(t_v v1, t_v v2)
{
	t_v mid;
	t_v dir;

	dir = v_subtract(v2, v1);
	mid = v_add(v1, v_scalar_mult(dir, 0.5));
	return (mid);
}
