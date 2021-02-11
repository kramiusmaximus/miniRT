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
# define NUM_THREADS 8
# define N_PASSES	1



typedef struct		s_v
{
	double 			x;
	double 			y;
	double 			z;
}					t_v;

typedef struct 		s_dims
{
	int 			height;
	int				width;
}					t_dims;

typedef struct		s_camera
{
	t_v			coordinates;
	t_v 		dir;
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
	t_v			coordinates;
	int 			color;
	struct s_light	*next;
}					t_light;

// shapes

typedef struct		s_sp
{
	t_v			coordinates;
	double 			diameter;
}					t_sp;

typedef struct		s_pl
{
	t_v			coordinates;
	t_v 		normal;
}					t_pl;

typedef struct		s_sq
{
	t_v			coordinates;
	t_v 		top;
	t_v			front;
	t_v 		side;
	double 			side_len;
}					t_sq;

typedef	struct		s_cy
{
	t_v			coordinates;
	t_v 		normal;
	double 			diameter;
	double 			height;
}					t_cy;

typedef struct 		s_tr
{
	t_v			p1;
	t_v			p2;
	t_v			p3;
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
	t_shape			data;
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
	double 		adjustment_factor;
	int 		parked;
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

typedef struct 		s_nav
{
	int 			fwd_back;
	int 			lft_rght;
	int 			up_dwn;
}					t_nav;

typedef struct 		s_vars
{
	t_mlx			*mlx;
	t_scene			*scene;
	t_nav			nav;
}					t_vars;

typedef struct			s_intersect
{
	double 				t;
	t_object			*obj;
	t_v 				contact;
	t_v					surface_v;
	int 				inside;
	struct s_intersect	*next;       // later can implement sorted list
}						t_intersect;

typedef struct 			s_ray
{
	t_v 			origin;
	t_v				dir;
	t_intersect			*intersect;
}						t_ray;

typedef struct			s_t
{
	int 				size;
	double 				closest;
	double 				arr[10];
}						t_t;

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
int 			rgb_subtract(int c1, int c2);


// vector functions
t_v				v_add(t_v v1, t_v v2);
t_v				v_subtract(t_v v1, t_v v2);
double			v_dot(t_v v1, t_v v2);
double 			v_norm(t_v v);
t_v 			v_scalar_mult(t_v v, double s);
t_v 			v_normalize(t_v v);
t_v 			v_random(t_v v, double amount);
t_v 			v_cross(t_v v1, t_v v2);
double			point_line_dist(t_v x0, t_v x1, t_v p);

// maths
int				solve_quadratic(double a, double b, double c, double t[2]);
t_v 			canvas_to_coords(int x_pixel, int y_pixel, t_scene *scene);
int 			min(int a, int b);
int 			max(int a, int b);
int 			abs(int a);


// ray tracing funcitions
int 			render_image();
t_object		*ray_intersect_sphere(t_v p_origin, t_v v_dir, t_object *sphere_obj, double *t);
t_object		*ray_intersect_plane(t_v p_origin, t_v v_dir, t_object *pl_obj, double *t);
t_object		*ray_intersect_sq(t_v p_origin, t_v v_dir, t_object *sq_object, double *t);
int 			ray_intersect_sausage(t_v p_origin, t_v v_dir, t_object *cy_object, double *t);
int 			ray_intersect_caps(t_v p_origin, t_v v_dir, t_object *cy_object, double *t, int solution_n);

t_v 			surface_vector(t_object *obj, t_v p_contact);
int 			process_light(t_object *obj, t_v contact_p, t_scene *scene, t_v pixel_ray);
t_object 		*trace_result(t_v p_origin, t_v v_dir, double *closest_t, t_scene *scene, double d);
int				trace_ray(t_v origin, t_v dir, t_scene *scene);

// movement
int 			move_camera(t_vars *vars);
int 			button_press(int key, t_vars *vars);
int				button_release(int key, t_vars *vars);
int				is_moving(t_nav *nav);

// new functions

t_v 			surface_vector_new(t_ray *ray, t_object *obj, t_intersect *inter);
t_intersect		*process_t(t_ray *ray, t_object *obj, t_t *t);


#endif
