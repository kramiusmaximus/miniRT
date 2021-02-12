#ifndef NAVIGATION_H
# define NAVIGATION_H

typedef struct		s_camera
{
	t_v				coordinates;
	t_v 			dir;
	double 			fov;
	int 			d;
	struct s_camera	*next;
}					t_camera;

typedef struct 		s_dims
{
	int 			height;
	int				width;
}					t_dims;

typedef struct		s_scene
{
	t_dims			window_dims;
	t_dims			res;
	double 			adjustment_factor;
	int 			parked;
	t_camera		*camera;
	t_light			*light;
	t_ambient		ambient;
	t_object		*object;
}					t_scene;

typedef struct  	s_image
{
	void        	*img;
	char        	*addr;
	int         	bits_per_pixel;
	int         	line_length;
	int         	endian;
}               	t_image;


#endif
