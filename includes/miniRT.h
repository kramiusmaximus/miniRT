#ifndef MINIRT_MINIRT_H
# define MINIRT_MINIRT_H
# include <math.h>
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# define SPHERE		0b1
# define MAX_DIST	10000000000

typedef struct  s_image
{
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
}               t_image;

typedef struct  s_vars
{
	void        *mlx;
	void        *win;
	t_image 	image;
}               t_vars;

typedef struct	s_vector
{
	int			count;
	double		arr[10];
}				t_vector;

typedef struct 	s_res
{
	int 		height;
	int			width;
}				t_res;

typedef	struct	s_canvas
{
	int 	pixel_width;
	int 	pixel_height;
}				t_canvas;

typedef struct 	s_rot
{
	double 		x_rot;
	double 		y_rot;
	double 		z_rot;
}				t_rot;

typedef struct	s_camera
{
	int 		id;
	t_vector	coordinates;
	t_rot		rotation;
	double 		fov;
	int 		d;
}				t_camera;

typedef struct	s_abmient
{
	double 		intensity;
	int 		color;
}				t_ambient;

typedef struct	s_light
{
	double		intensity;
	t_vector	coordinates;
	int 		color;

}				t_light;

typedef struct	s_lights
{
		int 	count;
		t_light	arr[10];
}				t_lights;

typedef struct	s_sphere
{
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

typedef struct	s_objects
{
	int 		count;
	void 		*arr[20];
}				t_objects;

typedef struct	s_scene
{
	t_res		res;
	t_camera	camera;
	t_lights	lights;
	t_ambient	ambient;
	t_spheres	spheres; // will remove later because objects are superior!!!
	t_objects	objects;
}				t_scene;

// color functions
int			get_t(int trgb);
int			get_r(int trgb);
int			get_g(int trgb);
int			get_b(int trgb);
int			create_trgb(int t, int r, int g, int b);
int			put_pixel(t_image *image, int x, int y, int color);

// vector functions
t_vector	vector_add(t_vector v1, t_vector v2);
t_vector	vector_subtract(t_vector v1, t_vector v2);
double		vector_dot(t_vector v1, t_vector v2);

t_vector canvas_to_coords(int cx, int cy, t_scene *scene);

// ray tracing funciotons
int render_image(t_vars *vars, t_scene *scene);
int trace_ray(t_vector cam_coords, t_vector c_coords, t_spheres spheres);
void ray_intersect_sphere(t_vector cam_coords, t_vector c_coords, t_sphere sphere, double t[2]);



#endif
