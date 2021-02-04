#include "miniRT.h"

t_3dvec canvas_to_coords(int cx, int cy, t_scene *scene)
{
	t_3dvec		coords;
	t_camera	*cam = scene->camera;

	double pixel_width = scene->camera->d * 2 * tan(scene->camera->fov / 2 * M_PI / 180) / scene->res.width;

	coords.x = (cx - (scene->res.width / 2)) * pixel_width + cam->coordinates.x;
	coords.y = -(cy - (scene->res.height / 2)) * pixel_width + cam->coordinates.y;
	coords.z = pixel_width * scene->res.width / (2 * tan(scene->camera->fov / 2 * M_PI / 180)) + cam->coordinates.z;
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