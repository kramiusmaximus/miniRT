#include "miniRT.h"

void put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel/ 8));
	*(unsigned int *)dst = color;
}

int		get_t(int trgb)
{
	return (trgb & (0xFF << 24));
}

int		get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

int		get_g(int trgb)
{
	return (trgb & (0xFF << 8));
}

int		get_b(int trgb)
{
	return (trgb & 0xFF);
}

int create_trgb(int t, int r, int f, int b)
{
	int res;

	if (t < 0 || t > 255 || r < 0 || r > 255 || f < 0 || f > 255 || b < 0 || b > 255)
		res = 0; // include ft_printf error message
	else
		res = (t << 8 | r << 8 | f << 8 | b);
	return (res);
}

int	main(void)
{
	void	*mlx;
	void 	*mlx_window;
	t_data	img;

	mlx = mlx_init();
	mlx_window = mlx_new_window(mlx, 1280, 720, "hello, world!");
	img.img = mlx_new_image(mlx, 1280, 720);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	for (int y = 0; y < 720; y++)
	{
		for (int x = 0; x < 1280; x++)
		{
			if (pow((double)(x - 640), 2) + pow((double)(y - 360), 2) < pow(250, 2))
				put_pixel(&img, x, y, 0x00FF0000);
			if (x > 600 && x < 680 && y > 320 && y < 400)
				put_pixel(&img, x, y, 0x000000FF);
			// mlx_pixel_put(mlx, mlx_window, x, y, 0x00FF0000); apparently live render is slower than render in buffer
		}
	}
	mlx_put_image_to_window(mlx, mlx_window, img.img, 0, 0);
	mlx_loop(mlx);
}
