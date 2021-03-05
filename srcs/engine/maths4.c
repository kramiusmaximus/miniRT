#include "miniRT.h"

t_m v_mat_mul(t_m a1, t_m a2)
{
	t_m res;
	int ijk[3];

	res.size[0] = a1.size[0];
	res.size[1] = a2.size[1];
	if (a1.size[1] != a2.size[0])
		ft_printf("Matrix size mismatch!\n");
	ijk[0] = 0;
	while (ijk[0] < a1.size[0])
	{
		ijk[1] = 0;
		while (ijk[1] < a2.size[1])
		{
			res.m[ijk[0]][ijk[1]] = 0;
			ijk[2] = 0;
			while (ijk[2] < a1.size[1])
			{
				res.m[ijk[0]][ijk[1]] += a1.m[ijk[0]][ijk[2]] * a2.m[ijk[2]][ijk[1]];
				ijk[2]++;
			}
			ijk[1]++;
		}
		ijk[0]++;
	}
	return (res);
}

t_m rotate_x(double alpha)
{
	t_m 	m;

	m.size[0] = 3;
	m.size[1] = 3;
	m.m[0][0] = 1;
	m.m[0][1] = 0;
	m.m[0][2] = 0;
	m.m[1][0] = 0;
	m.m[1][1] = cos(alpha);
	m.m[1][2] = -sin(alpha);
	m.m[2][0] = 0;
	m.m[2][1] = sin(alpha);
	m.m[2][2] = cos(alpha);
	return (m);
}

t_m rotate_y(double beta)
{
	t_m 	m;

	m.size[0] = 3;
	m.size[1] = 3;
	m.m[0][0] = cos(beta);
	m.m[0][1] = 0;
	m.m[0][2] = sin(beta);
	m.m[1][0] = 0;
	m.m[1][1] = 1;
	m.m[1][2] = 0;
	m.m[2][0] = -sin(beta);
	m.m[2][1] = 0;
	m.m[2][2] = cos(beta);
	return (m);
}

t_m rotate_z(double gamma)
{
	t_m 	m;

	m.size[0] = 3;
	m.size[1] = 3;
	m.m[0][0] = cos(gamma);
	m.m[0][1] = -sin(gamma);
	m.m[0][2] = 0;
	m.m[1][0] = sin(gamma);
	m.m[1][1] = cos(gamma);
	m.m[1][2] = 0;
	m.m[2][0] = 0;
	m.m[2][1] = 0;
	m.m[2][2] = 1;
	return (m);
}

t_m rotate_xyz(double pitch, double yaw, double roll, t_m basis)
{
	basis = v_mat_mul(rotate_x(pitch), basis);
	basis = v_mat_mul(rotate_y(yaw), basis);
	basis = v_mat_mul(rotate_z(roll), basis);
	return (basis);
}
