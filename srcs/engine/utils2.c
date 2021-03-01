#include "miniRT.h"

int 		selection_sort(double arr[], int size)
{
	int i;
	int j;
	double min;
	if (!arr)
		return (1);
	i = 0;
	while (i < size)
	{
		min = arr[i];
		j = i + 1;
		while (j < size)
		{
			if (arr[j] < min)
			{
				swap(&arr[i], &arr[j]);
				min = arr[j];
			}
			j++;
		}
		i++;
	}
	return (0);
}

t_v 	v_make(double x, double y, double z)
{
	t_v res;

	res.v[0] = x;
	res.v[1] = y;
	res.v[2] = z;
	return (res);
}

t_m 	m_i(int n)
{
	int i;
	int j;
	t_m	m;

	m.size[0] = n;
	m.size[1] = n;
	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < n)
		{
			m.m[i][j] = i == j ? 1 : 0;
			j++;
		}
		i++;
	}
	return m;
}

t_m 	obj_dir_transform(t_m basis, t_v dir)
{
	double rot[3];

	rot[0] = atan(-dir.v[1] / dir.v[2]);
	if (dir.v[2] < EPS && dir.v[2] > -EPS)
		rot[0] = atan(dir.v[1]/ EPS);
	rot[1] = atan(dir.v[0] / dir.v[2]);
	if (dir.v[2] < EPS && dir.v[2] > -EPS)
		rot[1] = atan(dir.v[0]/ EPS);
	if (dir.v[2] < 0)
		rot[1] += M_PI;
	rot[2] = 0;
	basis = rotate_xyz(rot[0], rot[1], rot[2], basis);
	return (basis);
}

t_m 	obj_norm_transform(t_m basis, t_v norm)
{
	double rot[3];

	// x rotation
	rot[0] = atan(sqrt(pow(norm.v[2], 2) + pow(norm.v[0], 2)) / norm.v[1]);
	if (norm.v[1] < EPS && norm.v[1] > -EPS)
		rot[0] = atan(sqrt(pow(norm.v[2], 2) + pow(norm.v[0], 2))/ EPS);
	if (norm.v[1] < 0)
		rot[0] += M_PI;

	basis = rotate_xyz(rot[0], 0, 0, basis);

	// y rotation
	rot[1] = atan(norm.v[0] / norm.v[2]);
	if (norm.v[2] < EPS && norm.v[2] > -EPS)
		rot[1] = atan(norm.v[0]/ EPS);
	if (norm.v[2] < 0)
		rot[1] += M_PI;

	basis = rotate_xyz(0, rot[1], 0, basis);

	return (basis);
}
