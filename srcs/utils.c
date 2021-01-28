#include <miniRT.h>

t_vector	*canvas_to_coords(int cx, int cy, double d)
{
	t_vector *coords;

	if (!(coords = (t_vector *)malloc(sizeof(t_vector))))
		return (NULL);
	coords->x = (double)cx;
	coords->y = (double)cy;
	coords->z = d;
	return (coords);
}

int put_pixel(t_image *data, int x, int y, int color)
{
	char	*p;

	if (!data)
		return (-1);
	p = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)p = color;
	return (0);
}