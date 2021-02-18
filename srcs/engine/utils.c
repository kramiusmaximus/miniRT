#include "miniRT.h"

t_v 		canvas_to_coords(int x_pixel, int y_pixel, t_scene *scene)
{
	t_v		coords;
	t_camera	*cam = scene->camera->content;
	double 		af = scene->adjustment_factor;
	double 		pixel_width = 2 * tan(cam->fov / 2 * M_PI / 180) / scene->res.width;

	coords.v[0] = (x_pixel - (scene->res.width * af / 2)) * pixel_width + cam->coord.v[0];
	coords.v[1] = -(y_pixel - (scene->res.height * af / 2)) * pixel_width + cam->coord.v[1];
	coords.v[2] = pixel_width * scene->res.width * af / (2 * tan(cam->fov / 2 * M_PI / 180)) + cam->coord.v[2];

	return (coords);
}

int 		put_pixel(t_image *image, int x, int y, int color)
{
	char	*p;

	if (!image)
	{
		ft_printf("Error at function \'put_pixel()\'\n");
		exit(1);
	}
	p = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int *)p = color;
	return (0);
}

t_intersect	*process_t(t_ray *ray, t_object *obj, t_t *t)
{
	t_intersect *inter;

	if (!ray || !obj || !t || !(inter = malloc(sizeof(t_intersect))))
	{
		ft_printf("Error at function \'process_t()\'\n");
		exit(1);
	}
	inter->t = t->closest;
	inter->contact = v_add(ray->origin, v_scalar_mult(ray->dir, inter->t));
	inter->obj = obj;
	inter->surface_v = surface_vector(ray, inter, obj);
	inter->surface_v = v_dot(inter->surface_v , ray->dir) > 0 ? v_scalar_mult(inter->surface_v,-1) : inter->surface_v;
	inter->ref_dir = v_subtract(ray->dir,v_scalar_mult(inter->surface_v , 2 * v_dot(inter->surface_v, ray->dir)));
	//inter->next;
	/// inter->inside = is_indside(inter);  inside function needs to be created
	return (inter);
}

t_ray		make_ray(t_v origin, t_v dir)
{
	t_ray ray;
	ray.origin = origin;
	ray.dir = dir;
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

double determinant(double a[25][25], double k)
{
	double s = 1, det = 0, b[25][25];
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
/*Finding transpose of matrix*/
void transpose(double num[25][25], double fac[25][25], double r)
{
	int i, j;
	double b[25][25], inverse[25][25], d;

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
	printf("\n\n\nThe inverse of matrix is : \n");

	for (i = 0;i < r; i++)
	{
		for (j = 0;j < r; j++)
		{
			printf("\t%f", inverse[i][j]);
		}
		printf("\n");
	}
}
void cofactor(double num[25][25], double f)
{
	double b[25][25], fac[25][25];
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