#include "miniRT.h"

t_v canvas_to_coords(int x_pixel, int y_pixel, t_scene *scene)
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

int put_pixel(t_image *image, int x, int y, int color)
{
	char	*p;

	if (!image)
		return (-1);
	p = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int *)p = color;
	return (0);
}

t_intersect *process_t(t_ray *ray, t_object *obj, t_t *t)
{
	t_intersect *head;
	t_intersect *p;
	int 		i;

	i = 0;
	head = NULL;
	if (!obj || !t || !t->size)
		return (head);
	if (!(head = malloc(sizeof(t_intersect))))
	{} /// crash function
	p = head;
	while (i < t->size)
	{
		p->t = t[i];
		p->obj = obj;
		p->contact = v_add(ray->origin, v_scalar_mult(ray->dir, t[i++]));
		p->surface_v = surface_vector_new(ray, obj, p);
		///head->inside;
		if (i < solutions_n)
		{
			if ((p->next = malloc(sizeof(t_intersect))))
			{} /// crash function
			p = p->next;
		}
	}
	return (head);
}