#include "miniRT.h"

t_v 		canvas_to_coords(int x_pixel, int y_pixel, t_scene *scene)
{
	t_v		coords;
	t_camera	*cam = scene->camera;
	double 		af = scene->adjustment_factor;
	double 		pixel_width = scene->camera->d * 2 * tan(scene->camera->fov / 2 * M_PI / 180) / scene->res.width;

	coords.x = (x_pixel - (scene->res.width * af / 2)) * pixel_width + cam->coordinates.x;
	coords.y = -(y_pixel - (scene->res.height * af / 2)) * pixel_width + cam->coordinates.y;
	coords.z = pixel_width * scene->res.width * af / (2 * tan(scene->camera->fov / 2 * M_PI / 180)) +
			cam->coordinates.z;

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
	inter->next;
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