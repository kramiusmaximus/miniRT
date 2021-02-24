#ifndef MAIN_STRUCTS_H
# define MAIN_STRUCTS_H
# include "../libft/includes/libft.h"
# include "bitmap.h"

typedef struct			s_intersect
{
	double 				t;
	t_object			*obj;
	t_v 				contact;
	t_v					ref_dir;
	t_v					surface_v;
	int 				inside;
}						t_intersect;

typedef struct 			s_ray
{
	t_v 				origin;
	t_v					dir;
	t_intersect			*intersect;
}						t_ray;

typedef struct		s_camera
{
	t_v				coord;
	t_v 			dir;
	t_m				basis;
	double 			fov;
}					t_camera;

typedef struct			s_listc
{
	t_camera			*content;
	struct s_listc		*prev;
	struct s_listc		*next;
}						t_listc;

typedef struct 		s_dims
{
	int 			height;
	int				width;
}					t_dims;

typedef struct		s_scene
{
	int 			s;
	t_dims			res;
	t_ambient		ambient;
	t_listc			*camera;
	t_list			*light;
	t_list			*object;
}					t_scene;

typedef struct  	s_image
{
	void        	*img;
	char        	*addr;
	int         	bits_per_pixel;
	int         	line_length;
	int         	endian;
}               	t_image;

typedef struct  	s_mlx
{
	void        	*mlx;
	void        	*win;
	t_dims 			window_dims;
	t_image 		image;
}               	t_mlx;

typedef struct 		s_nav
{
	int 			fwd_back;
	int 			lft_rght;
	int 			up_dwn;
	int 			rot_lft_rght;
	int 			rot_up_dwn;
}					t_nav;

typedef struct 		s_vars
{
	t_BMPImage 		bmpim;
	unsigned int 	*image;
	t_mlx			mlx;
	t_scene			scene;
	int 			rendered;
	double 			af;
	t_nav			nav;
}					t_vars;

typedef struct 		s_tvars
{
	t_vars			*vars;
	int 			tid;
}					t_tvars;

typedef struct 		s_render
{
	t_vars			*vars;
	int 			tid;
	t_scene			*scene;
	t_v 			vec[2];
	double 			mult[2];
	int 			color;
	t_ray			ray;
}					t_render;

#endif
