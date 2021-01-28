#ifndef MINIRT_MINIRT_H
# define MINIRT_MINIRT_H
# include <math.h>
# include <mlx.h>
# include <stdlib.h>
# define SPHERE		0b1
# define MAX_DIST	10000000

typedef struct  s_image {
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
}               t_image;

typedef struct  s_vars {
	void        *mlx;
	void        *win;
	t_image 	image;
}               t_vars;

typedef struct	s_vector {
	double 		x;
	double		y;
	double 		z;
}				t_vector;

typedef struct 	s_res {
	int 		height;
	int			width;
}				t_res;

typedef	struct	s_canvas {
	int 	pixel_width;
	int 	pixel_height;
}				t_canvas;

typedef struct 	s_rot {
	double 		x_rot;
	double 		y_rot;
	double 		z_rot;
}				t_rot;

typedef struct	s_camera {
	int 		id;
	t_vector	coordinates;
	t_rot		rotation;
	double 		fov;
	int 		d;
}				t_camera;

typedef struct	s_sphere {
	int 		id;
	double 		diameter;
	t_vector	coordinates;
	int 		color;
}				t_sphere;

typedef struct	s_spheres
{
	int			count;
	t_sphere	arr[10];	// change to pointer later
}				t_spheres;

int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);
int		create_trgb(int t, int r, int g, int b);
int		put_pixel(t_image *data, int x, int y, int color);

#endif
