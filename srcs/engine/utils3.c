/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:15:16 by pfelipa           #+#    #+#             */
/*   Updated: 2021/03/09 14:15:17 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

void put_pixel(t_render *rvars, int x, int y, int bpp)
{
	void	*p;
	t_vars *vars;

	vars = rvars->vars;
	if (!vars->mlx.image.addr)
	{
		ft_printf("Error at function \'put_pixel()\'\n");
		exit(1);
	}
	p = vars->mlx.image.addr + (y * vars->mlx.image.line_length + x * (bpp / 8));
	*(unsigned int *)p = rvars->color;
}

void put_pixel_bmp(t_bmpcrabs *crabs)
{
	unsigned int	*p;

	if (!crabs->img_addr)
	{
		ft_printf("Error at function \'put_pixel()\'\n");
		exit(1);
	}
	p = crabs->img_addr + (crabs->y * crabs->line_len + crabs->x * crabs->bpp / 8);

	((t_bmp_pix *)p)->r = (unsigned char)get_r(crabs->c);
	((t_bmp_pix *)p)->g = (unsigned char)get_g(crabs->c);
	((t_bmp_pix *)p)->b = (unsigned char)get_b(crabs->c);
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
			put_pixel(rvars, x, y, 32);
			x++;
		}
		y++;
	}
}
