#include "miniRT.h"

int free_mem(t_scene *scene)
{
	ft_lstclear(&scene->light, NULL);
	ft_lstclear(&scene->object, NULL);
	ft_lstcclear(&scene->camera);
}

int error(char *msg, t_scene *scene)
{
	free_mem(scene);
	if (msg)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(msg, 2);
		ft_putchar_fd('\n', 2);
		exit(228);
	}
	perror(NULL);
	exit(errno);
}

int put_pixel_bmp(void *img, int x, int y, int color, int line_len, int bpp)
{
	unsigned int	*p;
	int 	i;

	if (!img)
	{
		ft_printf("Error at function \'put_pixel()\'\n");
		exit(1);
	}
	i = 0;
	p = img + (y * line_len + x * bpp / 8);

	((bmp_pix *)p)->r = (unsigned char)get_r(color);
	((bmp_pix *)p)->g = (unsigned char)get_g(color);
	((bmp_pix *)p)->b = (unsigned char)get_b(color);
	return (0);
}
