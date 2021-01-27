#include "miniRT.h"
#include <stdio.h>

typedef struct	s_ball
{
	int x;
	int y;
}				t_ball;

typedef struct  s_vars {
	void        *mlx;
	void        *win;
	t_data 		image;
	int 		frame;
	t_ball		ball;
}               t_vars;

int 	change_ball_pos(int key, t_vars *vars)
{
	if (key == 13)
		vars->ball.y -= 10;
	else if (key == 1)
		vars->ball.y += 10;
	else if (key == 0)
		vars->ball.x -= 10;
	else if (key == 2)
		vars->ball.x += 10;
}

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

int create_trgb(int t, int r, int g, int b)
{
	int res;

	res = (t << 24 | r << 16 | g << 8 | b);
	return (res);
}

int	render_next_frame(t_vars *vars)
{
	//vars->image.img = mlx_new_image(vars->mlx, 1280, 720);
	//vars->image.addr = mlx_get_data_addr(vars->image.img, &vars->image.bits_per_pixel, &vars->image.line_length, &vars->image.endian);
	for (int y = 0; y < 720; y++)
	{
		for (int x = 0; x < 1280; x++)
		{
			if (pow((double)(x - 640 - vars->ball.x), 2) + pow((double)(y - 360 - vars->ball.y), 2) < pow(250, 2))
				put_pixel(&vars->image, x, y, create_trgb(0, 255, 2*vars->frame, 4*vars->frame));
			else
				put_pixel(&vars->image, x, y, create_trgb(0,0,0,0));
			// mlx_pixel_put(mlx, mlx_window, x, y, 0x00FF0000); apparently live render is slower than render in buffer
		}
	}
	vars->frame++;
	mlx_put_image_to_window(vars->mlx, vars->win, vars->image.img, 0, 0);
}


int             main(void)
{
	t_vars      vars;
	int res;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1280, 720, "hello, world!");
	vars.frame = 0;
	vars.ball.x = 0;
	vars.ball.y = 0;
	vars.image.img = mlx_new_image(vars.mlx, 1280, 720);
	vars.image.addr = mlx_get_data_addr(vars.image.img, &vars.image.bits_per_pixel, &vars.image.line_length, &vars.image.endian);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_key_hook(vars.win, change_ball_pos, &vars);
	mlx_loop(vars.mlx);
}