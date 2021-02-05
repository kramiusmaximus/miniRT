#ifndef MINIRT_MINIRT_H
# define MINIRT_MINIRT_H
# include <math.h>
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# define MAX_DIST	1000000000
# define SP			0b00000001
# define PL			0b00000010
# define SQ			0b00000100
# define CY			0b00001000
# define TR			0b00010000
# define NUM_THREADS 4

typedef struct		s_3dvec
{
	double 			x;
	double 			y;
	double 			z;
}					t_3dvec;

typedef struct 		s_dims
{
	int 			height;
	int				width;
}					t_dims;

typedef struct 		s_rot
{
	double 			x_rot;
	double 			y_rot;
	double 			z_rot;
}					t_rot;

typedef struct		s_camera
{
	t_3dvec			coordinates;
	t_rot			rotation;
	double 			fov;
	int 			d;
	struct s_camera	*next;
}					t_camera;

typedef struct		s_ambient
{
	double 			intensity;
	int 			color;
}					t_ambient;

typedef struct		s_light
{
	double			intensity;
	t_3dvec			coordinates;
	int 			color;
	struct s_light	*next;
}					t_light;



// shapes

typedef struct		s_sp
{
	t_3dvec			coordinates;
	double 			diameter;
}					t_sp;

typedef struct		s_pl
{
	t_3dvec			coordinates;
	t_rot			rotation;
}					t_pl;

typedef struct		s_sq
{
	t_3dvec			coordinates;
	t_rot			rotation;
	double 			side_len;
}					t_sq;

typedef	struct		s_cy
{
	t_3dvec			coordinates;
	t_rot			rotation;
	double 			diameter;
	double 			height;
}					t_cy;

typedef struct 		s_tr
{
	t_3dvec			p1;
	t_3dvec			p2;
	t_3dvec			p3;
}					t_tr;

typedef union		u_shape
{
	t_sp			sp;
	t_pl			pl;
	t_sq			sq;
	t_cy			cy;
	t_tr			tr;
}					t_shape;

typedef struct		s_object
{
	int 			type;
	t_shape			shape;
	double 			refraction;
	double 			reflectivity;
	int 			color;
	struct s_object	*next;
}				t_object;




// main structure which stores most of data after parsing

typedef struct	s_scene
{
	t_dims		window_dims;
	t_dims		res;
	t_camera	*camera;
	t_light		*light;
	t_ambient	ambient;
	t_object	*object;
}				t_scene;


// MLX

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
	t_image 		image;
}               	t_mlx;

typedef struct 		s_vars
{
	t_mlx			*mlx;
	t_scene			*scene;
}					t_vars;

typedef struct		s_targs
{
	t_vars			*vars;
	int 			id;
}					t_targs;


// color functions

int				get_t(int trgb);
int				get_r(int trgb);
int				get_g(int trgb);
int				get_b(int trgb);
int				rgb_create(int t, int r, int g, int b);
int				put_pixel(t_image *image, int x, int y, int color);
int				rgb_multiply(int c1, int c2);
int				rgb_multiply_scalar(int c1, double s);
int				rgb_add(int c1, int c2);

// vector functions
t_3dvec			vector_add(t_3dvec v1, t_3dvec v2);
t_3dvec			vector_subtract(t_3dvec v1, t_3dvec v2);
double			vector_dot(t_3dvec v1, t_3dvec v2);
double 			vector_norm(t_3dvec v);
t_3dvec 		vector_scalar_mult(t_3dvec v, double s);
t_3dvec 		vector_normalize(t_3dvec v);

// maths
int				solve_quadratic(double a, double b, double c, double t[2]);
t_3dvec 		canvas_to_coords(int cx, int cy, t_scene *scene);

// ray tracing funcitions
int render_image(t_vars *vars);
t_object		*ray_intersect_sphere(t_3dvec p_origin, t_3dvec v_dir, t_object *sphere_obj, double *t);
t_3dvec 		surface_vector(t_object *obj, t_3dvec p_contact);
int 			process_light(t_object *obj, t_3dvec contact_p, t_scene *scene);
t_object 		*trace_result(t_3dvec p_origin, t_3dvec v_dir, double *closest_t, t_scene *scene, double d);
int				trace_ray(t_3dvec cam_coords, t_3dvec v, t_scene *scene);

// movement
int 			move_camera(int key, t_vars *vars);


#endif
