#ifndef TRACING_H
# define TRACING_H
# include "main_structs.h"

typedef struct			s_t
{
	int 				size;
	double 				closest;
	double 				arr[10];
}						t_t;

int						ray_intersect_sphere(t_ray *ray, t_object *sp_obj, t_t *t);
int 					ray_intersect_plane(t_ray	*ray, t_object *pl_obj, t_t *t);
int 					ray_intersect_sq(t_ray *ray, t_object *sq_obj, t_t *t);
int 					ray_intersect_cy(t_ray	*ray, t_object *cy_obj, t_t *t);
int 					ray_intersect_tr(t_ray *ray, t_object *tr_obj, t_t *t);
t_ray make_ray(t_v origin, t_v dir, int inside);
t_intersect				*process_t(t_ray *ray, t_object *obj, t_t *t);
int						solve_quadratic(double a, double b, double c, t_t *t);
int 					min(int a, int b);
int 					max(int a, int b);
int 					abs(int a);
t_v surface_vector(t_intersect *inter, t_object *obj);
void light_effects(t_ray *ray, t_scene *scene, int *c, t_intersect *inter);
t_intersect *trace_result(t_ray *ray, t_scene *scene, double min_d, double max_d);
int trace_ray(t_ray *ray, t_scene *scene, int n_passes, double d_min, double d_max);
int 					swap(double *a, double *b);
int 					selection_sort(double arr[], int size);
t_v						screen_to_world(int h, int v, t_vars *vars);

#endif
