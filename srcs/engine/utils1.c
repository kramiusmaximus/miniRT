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

t_intersect *process_t(t_object *obj, t_ray *ray, t_t *t, t_scene *scene)
{
	t_intersect *inter;
	double 		c;
	double 		r;

	if (!ray || !obj || !t || !(inter = malloc(sizeof(t_intersect))))
		error("Failed malloc allocatoin.", scene);
	inter->t = t->closest;
	inter->contact = v_add(ray->origin, v_scalar_mult(ray->dir, inter->t));
	inter->obj = obj;
	inter->surface_v = surface_vector(inter, obj);
	inter->surface_v = v_dot(inter->surface_v , v_normalize(ray->dir)) > 0 ? v_scalar_mult(inter->surface_v,-1) :
			inter->surface_v;
	inter->incidence_ang0 = M_PI - acos(v_dot(v_normalize(ray->dir), inter->surface_v));
	inter->ref_dir = v_subtract(ray->dir,v_scalar_mult(inter->surface_v , 2 * v_dot(inter->surface_v, ray->dir)));
	c = -v_dot(inter->surface_v, v_normalize(ray->dir));
	if (obj->type & (SP | CY))
	{
		r = ray->inside ? inter->obj->refraction : 1 / inter->obj->refraction;
		inter->tra_dir = v_add(v_scalar_mult(v_normalize(ray->dir), r),
							   v_scalar_mult(inter->surface_v, r * c - sqrt(1 - pow(r, 2) * (1 - pow(c, 2)))));
	}
	else
		inter->tra_dir = ray->dir;
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
