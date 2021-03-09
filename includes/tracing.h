/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 15:56:47 by pfelipa           #+#    #+#             */
/*   Updated: 2021/03/08 15:56:49 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACING_H
# define TRACING_H
# include "main_structs.h"

typedef struct			s_ray_inter
{
	double				d[10];
	t_v					v[7];
	int					i;
}						t_ray_inter;

typedef struct			s_t
{
	int					size;
	double				closest;
	double				arr[10];
}						t_t;

typedef struct			s_trvars
{
	t_list				*p;
	t_object			*obj;
	t_object			*obj_closest;
	t_scene				*scene;
	t_t					t;
	int					i;
	int					err;
}						t_trvars;

int						ray_intersect_sphere(t_ray *ray,
						t_object *sp_obj, t_t *t);
int						ray_intersect_plane(t_ray	*ray,
						t_object *pl_obj, t_t *t);
int						ray_intersect_sq(t_ray *ray, t_object *sq_obj, t_t *t);
int						ray_intersect_cy(t_ray	*ray, t_object *cy_obj, t_t *t);
int						ray_intersect_tr(t_ray *ray, t_object *tr_obj, t_t *t);
t_ray					make_ray(t_v origin, t_v dir, int inside);
t_intersect				*process_t(t_object *obj,
						t_ray *ray, t_t *t, t_scene *scene);
int						solve_quadratic(double a, double b, double c, t_t *t);
t_v						surface_vector(t_intersect *inter, t_object *obj);
void					light_effects(t_ray *ray, t_scene *scene,
						int *c, t_intersect *inter);
t_intersect *trace_ray(t_ray *ray, t_scene *scene, double *d);
int trace_color(t_ray *ray, t_scene *scene, int n_passes, double *d);
int						swap(double *a, double *b);
int						selection_sort(double arr[], int size);
t_v						screen_to_world(int h, int v, t_vars *vars, int aa);
int						get_pixel_color(int v, int h, t_vars *vars);

#endif
