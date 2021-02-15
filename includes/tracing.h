#ifndef TRACING_H
#define TRACING_H

typedef struct			s_t
{
	int 				size;
	double 				closest;
	double 				arr[10];
}						t_t;


typedef struct			s_intersect
{
	double 				t;
	t_object			*obj;
	t_v 				contact;
	t_v					ref_dir;
	t_v					surface_v;
	int 				inside;
	struct s_intersect	*next;
}						t_intersect;

typedef struct 			s_ray
{
	t_v 				origin;
	t_v					dir;
	t_intersect			*intersect;
	t_v 				dir_ref;
	struct s_ray		*next;
}						t_ray;

int						ray_intersect_sphere(t_ray *ray, t_object *sp_obj, t_t *t);
int 					ray_intersect_plane(t_ray	*ray, t_object *pl_obj, t_t *t);
int 					ray_intersect_sq(t_ray *ray, t_object *sq_obj, t_t *t);
int 					ray_intersect_cy(t_ray	*ray, t_object *cy_obj, t_t *t);
int 					ray_intersect_tr(t_ray *ray, t_object *tr_obj, t_t *t);
t_ray					make_ray(t_v origin, t_v dir);
t_intersect				*process_t(t_ray *ray, t_object *obj, t_t *t);
int						solve_quadratic(double a, double b, double c, t_t *t);
t_v 					canvas_to_coords(int x_pixel, int y_pixel, t_scene *scene);
int 					min(int a, int b);
int 					max(int a, int b);
int 					abs(int a);
t_v 					surface_vector(t_ray *ray, t_intersect *inter, t_object *obj);
int process_light(t_ray *ray, t_scene *scene);
t_intersect 			*trace_result(t_ray *ray, t_scene *scene, double d);
int trace_ray(t_ray *ray, t_scene *scene, int n_passes, double d);
int 					swap(double *a, double *b);
int 					selection_sort(double arr[], int size);

#endif
