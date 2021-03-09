/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:40:34 by pfelipa           #+#    #+#             */
/*   Updated: 2021/03/08 16:40:36 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void		render_image_bmp(t_vars *vars)
{
	int			v;
	int			h;
	t_bmpcrabs	crabs;

	v = 0;
	while (v < vars->scene.res.ht)
	{
		h = 0;
		while (h < vars->scene.res.width)
		{
			crabs.img_addr = vars->bmpim.image + vars->bmpim.header.offset;
			crabs.x = h;
			crabs.y = v;
			crabs.c = get_pixel_color(vars->scene.res.ht - v, h, vars);
			crabs.line_len = (vars->bmpim.header.width_px * vars->bmpim.header.bits_per_pixel\
			/ 8 + vars->bmpim.pad_size);
			crabs.bpp = vars->bmpim.header.bits_per_pixel;
			put_pixel_bmp(&crabs);
			h++;
		}
		v++;
	}
}

void			bitmap_header(t_vars *vars)
{
	t_bmpheader	*header;

	header = &vars->bmpim.header;
	ft_bzero(header, sizeof(t_bmpheader));
	header->type = 0x4d42;
	header->offset = 54;
	header->dib_header_size = 40;
	header->width_px = vars->scene.res.width;
	header->height_px = vars->scene.res.ht;
	header->num_planes = 1;
	header->bits_per_pixel = 24;
	header->image_size_bytes = header->height_px * (header->width_px *\
	header->bits_per_pixel / 8 + vars->bmpim.pad_size);
	header->x_resolution_ppm = 2835;
	header->y_resolution_ppm = 2835;
	header->size = header->offset + header->image_size_bytes;
}

void			mlx_image_to_bmp(t_vars *vars)
{
	int			v;
	int			h;
	t_bmpcrabs	crabs;

	crabs.line_len = vars->bmpim.header.width_px *\
	vars->bmpim.header.bits_per_pixel / 8 + vars->bmpim.pad_size;
	v = 0;
	while (v < (int)(((double)vars->scene.res.ht)))
	{
		h = 0;
		while (h < (int)(((double)vars->scene.res.width)))
		{
			crabs.img_addr = vars->bmpim.image + vars->bmpim.header.offset;
			crabs.x = h;
			crabs.y = vars->mlx.window_dims.ht - v;
			crabs.c = *((int *)vars->mlx.image.addr + v * vars->bmpim.header.width_px + h);
			crabs.bpp = vars->bmpim.header.bits_per_pixel;
			put_pixel_bmp(&crabs);
			h++;
		}
		v++;
	}
}

void			screen_shot(t_vars *vars)
{
	int	fd;

	if ((fd = open("../miniRT_snapshot3.bmp", O_WRONLY | O_CREAT \
	| O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
		error(NULL, &vars->scene);
	vars->bmpim.pad_size = (4 - (vars->scene.res.width *\
	vars->bmpim.header.bits_per_pixel / 8) % 4) % 4;
	bitmap_header(vars);
	if (!(vars->bmpim.image = malloc(vars->bmpim.header.size)))
		error(NULL, &vars->scene);
	ft_memcpy(vars->bmpim.image, &vars->bmpim.header, sizeof(t_bmpheader));
	mlx_image_to_bmp(vars);
	write(fd, vars->bmpim.image, vars->bmpim.header.size);
	free(vars->bmpim.image);
	ft_printf("BMP image successfully created.\n");
}

void			create_bmp_image(t_vars *vars, char *filename)
{
	int	fd;

	if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC,\
	S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
		error(NULL, &vars->scene);
	vars->bmpim.pad_size = (4 - (vars->scene.res.width *\
	vars->bmpim.header.bits_per_pixel / 8) % 4) % 4;
	bitmap_header(vars);
	if (!(vars->bmpim.image = malloc(vars->bmpim.header.size)))
		error(NULL, &vars->scene);
	ft_memcpy(vars->bmpim.image, &vars->bmpim.header, sizeof(t_bmpheader));
	render_image_bmp(vars);
	write(fd, vars->bmpim.image, vars->bmpim.header.size);
	free(vars->bmpim.image);
	free_mem(&vars->scene);
	ft_printf("BMP image successfully created.\n");
}
