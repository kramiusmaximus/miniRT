#include "miniRT.h"

static int render_image_bmp(t_vars *vars)
{
	t_render	rvars;
	int 		offset;

	offset = vars->bmpim.header.offset;
	for (int v = 0; v < vars->scene.res.height; v++) //
	{
		for (int h = 0; h < vars->scene.res.width; h++)
		{
			rvars.vec[0] = screen_to_world(h, v, vars, 0);
			rvars.vec[1] = v_subtract(rvars.vec[0], ((t_camera *)vars->scene.camera->content)->coord);
			rvars.ray = make_ray(((t_camera *) vars->scene.camera->content)->coord, rvars.vec[1], 0);
			rvars.color = trace_color(&rvars.ray, &vars->scene, N_PASSES, 1, MAX_DIST);
			put_pixel_bmp(vars->bmpim.image + offset, h, v, rvars.color, (vars->bmpim.header.width_px * vars->bmpim.header.bits_per_pixel / 8 + vars->bmpim.pad_size), vars->bmpim.header.bits_per_pixel);
		}
	}
	return (0);
}

void bitmap_header(t_vars *vars)
{
	t_BMPHeader *header;

	header = &vars->bmpim.header;
	ft_bzero(header, sizeof(t_BMPHeader));
	header->type = 0x4d42; /// potential error
	header->offset = 54;
	header->dib_header_size = 40;
	header->width_px = vars->scene.res.width;
	header->height_px = vars->scene.res.height;
	header->num_planes = 1;
	header->bits_per_pixel = 24;
	header->image_size_bytes = header->height_px * (header->width_px * header->bits_per_pixel / 8 + vars->bmpim.pad_size);
	header->x_resolution_ppm = 2835;
	header->y_resolution_ppm = 2835;
	header->size = header->offset + header->image_size_bytes;
}

void mlx_image_to_bmp(t_vars *vars)
{
	/*
	int v;
	int h;
	int offset;
	int color;

	offset = vars->bmpim.header.offset;
	v = 0;
	while (v < vars->bmpim.header.height_px)
	{
		h = 0;
		while (h < vars->bmpim.header.width_px)
		{
			color = *((int *)vars->mlx.image.addr + v*vars->bmpim.header.width_px + h);
			put_pixel_bmp(vars->bmpim.image + offset, h, v, color, (vars->bmpim.header.width_px * vars->bmpim.header.bits_per_pixel / 8 + vars->bmpim.pad_size), vars->bmpim.header.bits_per_pixel);
			h++;
		}
		v++;
	}
	 */
	int offset;
	t_render rvars;

	offset = vars->bmpim.header.offset;
	rvars.mult[0] = ((double)vars->mlx.window_dims.height / (double)vars->scene.res.height) / vars->af;
	rvars.mult[1] = ((double)vars->mlx.window_dims.width / (double)vars->scene.res.width) / vars->af;
	for (int v = 0; v < vars->mlx.window_dims.height; v++) //
	{
		for (int h = 0; h < vars->mlx.window_dims.width; h++)
		{
			for (int y_pixel = (int)(v * rvars.mult[0]); y_pixel < (int)((double)(v + 1) * rvars.mult[0]); y_pixel++)
				for (int x_pixel = (int)(h * rvars.mult[1]); x_pixel < (int)((double)(h + 1) * rvars.mult[1]); x_pixel++)
				{
					/*put_pixel(vars->mlx.image.addr, x_pixel, y_pixel, rvars.color, vars->mlx.image.line_length,
							  vars->mlx.image.bits_per_pixel);
							  */
					rvars.color = *((int *)vars->mlx.image.addr + v*vars->bmpim.header.width_px + h);
					put_pixel_bmp(vars->bmpim.image + offset, h,vars->mlx.window_dims.height - v, rvars.color, (vars->bmpim.header.width_px * vars->bmpim.header.bits_per_pixel / 8 + vars->bmpim.pad_size), vars->bmpim.header.bits_per_pixel);
				}
		}
	}
}

void screen_shot(t_vars *vars)
{
	int	fd;

	if ((fd = open("../miniRT_snapshot3.bmp", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
		error(NULL, &vars->scene);
	vars->bmpim.pad_size = (4 - (vars->scene.res.width * vars->bmpim.header.bits_per_pixel / 8) % 4) % 4;
	bitmap_header(vars);
	if (!(vars->bmpim.image = malloc(vars->bmpim.header.size))) /// will need to free
		error(NULL, &vars->scene);
	ft_memcpy(vars->bmpim.image, &vars->bmpim.header, sizeof(t_BMPHeader));
	mlx_image_to_bmp(vars);
	write(fd, vars->bmpim.image, vars->bmpim.header.size);
	free(vars->bmpim.image);
	ft_printf("BMP image successfully created.\n");
}

void create_bmp_image(t_vars *vars, char *filename)
{
	int	fd;

	if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
		error(NULL, &vars->scene);
	vars->bmpim.pad_size = (4 - (vars->scene.res.width * vars->bmpim.header.bits_per_pixel / 8) % 4) % 4;
	bitmap_header(vars);
	if (!(vars->bmpim.image = malloc(vars->bmpim.header.size)))
		error(NULL, &vars->scene);
	ft_memcpy(vars->bmpim.image, &vars->bmpim.header, sizeof(t_BMPHeader));
	render_image_bmp(vars);
	write(fd, vars->bmpim.image, vars->bmpim.header.size);
	free(vars->bmpim.image);
	free_mem(&vars->scene);
	ft_printf("BMP image successfully created.\n");
}
