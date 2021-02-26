#include "miniRT.h"

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

static int render_image_bmp(t_vars *vars)
{
	t_render	rvars;
	int 		offset;

	offset = vars->bmpim.header.offset;
	for (int v = 0; v < vars->scene.res.height; v++) //
	{
		for (int h = 0; h < vars->scene.res.width; h++)
		{
			rvars.vec[0] = screen_to_world(h, v, vars);
			rvars.vec[1] = v_subtract(rvars.vec[0], ((t_camera *)vars->scene.camera->content)->coord);
			rvars.ray = make_ray(((t_camera *)vars->scene.camera->content)->coord, rvars.vec[1]);
			rvars.color = trace_ray(&rvars.ray, &vars->scene, N_PASSES, 1, MAX_DIST);
			put_pixel_bmp(vars->bmpim.image + offset, h, v, rvars.color, (vars->bmpim.header.width_px * vars->bmpim.header.bits_per_pixel / 8 + vars->bmpim.pad_size), vars->bmpim.header.bits_per_pixel);
		}
	}
	return (0);
}

int bitmap_header(t_vars *vars, int fd)
{
	t_BMPHeader *header;

	header = &vars->bmpim.header;
	ft_bzero(header, sizeof(t_BMPHeader));

	// file header
	header->type = 0x4d42; /// potential error
	header->offset = 54;

	// information header
	header->dib_header_size = 40;
	header->width_px = vars->scene.res.width;
	header->height_px = vars->scene.res.height;
	header->num_planes = 1;
	header->bits_per_pixel = 24;
	header->image_size_bytes = header->height_px * (header->width_px * header->bits_per_pixel / 8 + vars->bmpim.pad_size);
	header->x_resolution_ppm = 2835;
	header->y_resolution_ppm = 2835;

	// file size
	header->size = header->offset + header->image_size_bytes;
}

int create_bmp_image(t_vars *vars, char *filename)
{
	int 				fd;

	if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
		error(NULL, &vars->scene);
	vars->bmpim.pad_size = (4 - (vars->scene.res.width * vars->bmpim.header.bits_per_pixel / 8) % 4) % 4;
	bitmap_header(vars, fd);
	if (!(vars->bmpim.image = malloc(vars->bmpim.header.size))) /// will need to free
		error(NULL, &vars->scene);
	ft_memcpy(vars->bmpim.image, &vars->bmpim.header, sizeof(t_BMPHeader));
	render_image_bmp(vars);
	write(fd, vars->bmpim.image, vars->bmpim.header.size);
	free(vars->bmpim.image);
	ft_printf("BMP image successfully created.\n");
}
