#include "miniRT.h"

t_v v_create(double x1, double x2, double x3)
{
	t_v v;

	v.v[0] = x1;
	v.v[1] = x2;
	v.v[2] = x3;
	return (v);
}

t_v	v_add(t_v v1, t_v v2)
{
	v1.v[0] += v2.v[0];
	v1.v[1] += v2.v[1];
	v1.v[2] += v2.v[2];
	return (v1);
}

t_v	v_subtract(t_v v1, t_v v2)
{
	v1.v[0] -= v2.v[0];
	v1.v[1] -= v2.v[1];
	v1.v[2] -= v2.v[2];
	return (v1);
}

double		v_dot(t_v v1, t_v v2)
{
	return (v1.v[0] * v2.v[0] + v1.v[1] * v2.v[1] + v1.v[2] * v2.v[2]);
}

double		v_norm(t_v v)
{
	return (sqrt(pow(v.v[0], 2) + pow(v.v[1], 2) + pow(v.v[2], 2)));
}

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

int			solve_quadratic(double a, double b, double c, t_t *t)
{
	double discriminant;

	if (!t)
		return (1);
	discriminant = pow(b,2) - 4 * a * c;
	if (discriminant * 100000 == 0)
	{
		t->arr[0] = -b / (2 * a);
		t->size = 1;
	}
	else if (discriminant < 0)
		t->size = 0;
	else
	{
		t->arr[0] = (-b + sqrt(discriminant)) / (2 * a);
		t->arr[1] = (-b - sqrt(discriminant)) / (2 * a);
		t->size = 2;
	}
	return (0);
}

t_v v_mat_mul_vec(t_m m, t_v v)  /// would be interesting to see the difference in performance when using this func and
/// one with pointers
{
	int i;
	int j;
	t_v res = {0,0,0};

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			res.v[i] += m.m[i][j] * v.v[j];
			j++;
		}
		i++;
	}
	return (res);
}

t_m v_mat_mul(t_m a1, t_m a2)
{
	t_m res;
	int i;
	int j;
	int k;

	res.size[0] = a1.size[0];
	res.size[1] = a2.size[1];
	if (a1.size[1] != a2.size[0])
		ft_printf("Matrix size mismatch!\n");
	i = 0;
	while (i < a1.size[0])
	{
		j = 0;
		while (j < a2.size[1])
		{
			res.m[i][j] = 0;
			k = 0;
			while (k < a1.size[1])
			{
				res.m[i][j] += a1.m[i][k] * a2.m[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (res);
}

t_m rotate_x(double theta)
{
	t_m 	m;

	m.size[0] = 3;
	m.size[1] = 3;
	m.m[0][0] = 1;
	m.m[0][1] = 0;
	m.m[0][2] = 0;
	m.m[1][0] = 0;
	m.m[1][1] = cos(theta);
	m.m[1][2] = -sin(theta);
	m.m[2][0] = 0;
	m.m[2][1] = sin(theta);
	m.m[2][2] = cos(theta);
	return (m);
}

t_m rotate_y(double theta)
{
	t_m 	m;

	m.size[0] = 3;
	m.size[1] = 3;
	m.m[0][0] = cos(theta);
	m.m[0][1] = 0;
	m.m[0][2] = sin(theta);
	m.m[1][0] = 0;
	m.m[1][1] = 1;
	m.m[1][2] = 0;
	m.m[2][0] = -sin(theta);
	m.m[2][1] = 0;
	m.m[2][2] = cos(theta);
	return (m);
}

t_m m_transpose(t_m m)
{
	t_m trans;
	int i;
	int j;

	if (m.size[0]!= m.size[1])
		ft_printf("dims sizes are not equal\n");
	i = 0;
	m.size[0] = 3;
	m.size[1] = 3;
	while (i < m.size[0])
	{
		j = 0;
		while (j < m.size[0])
		{
			trans.m[i][j] = m.m[j][i];
			j++;
		}
		i++;
	}
	return (trans);
}

double	max_f(double a, double b)
{
	return (a > b ? a : b);
}

double min_f(double a, double b)
{
	return (a < b ? a : b);
}

double abs_f(double a)
{
	return (a > 0 ? -a : a);
}

double bound(double num, double lower_b, double upper_b)
{
	if (num > upper_b)
		return (upper_b);
	if (num < lower_b)
		return (lower_b);
	return (num);
}