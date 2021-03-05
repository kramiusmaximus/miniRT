#include "miniRT.h"

void free_mem(t_scene *scene)
{
	ft_lstclear(&scene->light, NULL);
	ft_lstclear(&scene->object, NULL);
	ft_lstcclear(&scene->camera);
}

void error(char *msg, t_scene *scene)
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

void put_pixel(void *img, int x, int y, int color, int line_len, int bpp)
{
	void	*p;

	if (!img)
	{
		ft_printf("Error at function \'put_pixel()\'\n");
		exit(1);
	}
	p = img + (y * line_len + x * (bpp / 8));
	*(unsigned int *)p = color;
}

void put_pixel_bmp(void *img, int x, int y, int color, int line_len, int bpp)
{
	unsigned int	*p;

	if (!img)
	{
		ft_printf("Error at function \'put_pixel()\'\n");
		exit(1);
	}
	p = img + (y * line_len + x * bpp / 8);

	((bmp_pix *)p)->r = (unsigned char)get_r(color);
	((bmp_pix *)p)->g = (unsigned char)get_g(color);
	((bmp_pix *)p)->b = (unsigned char)get_b(color);
}

void fill_square(t_render *rvars, int v, int h)
{
	int 	x;
	int 	y;
	t_vars 	*vars;

	vars = rvars->vars;
	y = (int)(v * rvars->mult[0]);
	while (y < (int)((double)(v + 1) * rvars->mult[0]))
	{
		x = (int) (h * rvars->mult[1]);
		while (x < (int) ((double) (h + 1) * rvars->mult[1]))
		{
			put_pixel(vars->mlx.image.addr, x, y, rvars->color, vars->mlx.image.line_length, 32);
			x++;
		}
		y++;
	}
}
