#include "miniRT.h"

int put_pixel(void *img, int x, int y, int color, int line_len, int bpp)
{
	void	*p;

	if (!img)
	{
		ft_printf("Error at function \'put_pixel()\'\n");
		exit(1);
	}
	p = img + (y * line_len + x * (bpp / 8));
	*(unsigned int *)p = color;

	return (0);
}

t_intersect	*process_t(t_ray *ray, t_object *obj, t_t *t)
{
	t_intersect *inter;
	double 		c;
	double 		r;

	if (!ray || !obj || !t || !(inter = malloc(sizeof(t_intersect))))
	{
		ft_printf("Error at function \'process_t()\'\n");
		exit(1);
	}
	inter->t = t->closest;
	inter->contact = v_add(ray->origin, v_scalar_mult(ray->dir, inter->t));
	inter->obj = obj;
	inter->surface_v = surface_vector(ray, inter, obj);
	inter->surface_v = v_dot(inter->surface_v , v_normalize(ray->dir)) > 0 ? v_scalar_mult(inter->surface_v,-1) :
			inter->surface_v;
	inter->incidence_ang0 = M_PI- acos(v_dot(v_normalize(ray->dir), inter->surface_v));
	inter->ref_dir = v_subtract(ray->dir,v_scalar_mult(inter->surface_v , 2 * v_dot(inter->surface_v, ray->dir)));
	// tra_dir calculation
	c = -v_dot(inter->surface_v, v_normalize(ray->dir));
	if (ray->inside) // if inside
		r = inter->obj->refraction;
	else                // if outside
		r = 1 / inter->obj->refraction;

	inter->tra_dir = v_add(v_scalar_mult(v_normalize(ray->dir), r) ,v_scalar_mult(inter->surface_v,r*c - sqrt(1-pow(r,2)*(1-pow
			(c,2)))));
	return (inter);
}

t_ray make_ray(t_v origin, t_v dir, int inside)
{
	t_ray ray;
	ray.origin = origin;
	ray.dir = dir;
	ray.inside = inside;
	ray.intersect = NULL;
	return (ray);
}

int 		swap(double *a, double *b)
{
	double temp;

	if (!a || !b)
		return (1);
	temp = *a;
	*a = *b;
	*b = temp;
	return (0);
}

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

double determinant(double a[3][3], double k)
{
	double s = 1, det = 0, b[3][3];
	int i, j, m, n, c;
	if (k == 1)
	{
		return (a[0][0]);
	}
	else
	{
		det = 0;
		for (c = 0; c < k; c++)
		{
			m = 0;
			n = 0;
			for (i = 0;i < k; i++)
			{
				for (j = 0 ;j < k; j++)
				{
					b[i][j] = 0;
					if (i != 0 && j != c)
					{
						b[m][n] = a[i][j];
						if (n < (k - 2))
							n++;
						else
						{
							n = 0;
							m++;
						}
					}
				}
			}
			det = det + s * (a[0][c] * determinant(b, k - 1));
			s = -1 * s;
		}
	}
	return (det);
}

void transpose(double num[3][3], double fac[3][3], double r)
{
	int i, j;
	double b[3][3], inverse[3][3], d;

	for (i = 0;i < r; i++)
	{
		for (j = 0;j < r; j++)
		{
			b[i][j] = fac[j][i];
		}
	}
	d = determinant(num, r);
	for (i = 0;i < r; i++)
	{
		for (j = 0;j < r; j++)
		{
			inverse[i][j] = b[i][j] / d;
		}
	}
}

void cofactor(double num[3][3], double f)
{
	double b[3][3], fac[3][3];
	int p, q, m, n, i, j;
	for (q = 0;q < f; q++)
	{
		for (p = 0;p < f; p++)
		{
			m = 0;
			n = 0;
			for (i = 0;i < f; i++)
			{
				for (j = 0;j < f; j++)
				{
					if (i != q && j != p)
					{
						b[m][n] = num[i][j];
						if (n < (f - 2))
							n++;
						else
						{
							n = 0;
							m++;
						}
					}
				}
			}
			fac[q][p] = pow(-1, q + p) * determinant(b, f - 1);
		}
	}
	transpose(num, fac, f);
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

void	ft_lstcclear(t_listc **lst)
{
	t_listc *current;
	t_listc *next;

	if (lst && *lst)
	{
		current = *lst;
		while (current != *lst)
		{
			next = current->next;
			free(current->content);
			free(current);
			current = next;
		}
		*lst = NULL;
	}
}