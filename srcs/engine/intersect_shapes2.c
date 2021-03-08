/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_shapes2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:31:46 by pfelipa           #+#    #+#             */
/*   Updated: 2021/03/08 17:31:48 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int		ray_intersect_sausage(t_ray *ray, t_object *cy_obj, t_t *t)
{
	t_ray_inter	s;
	t_cy		*cy;

	if (!ray || !cy_obj || !t)
		return (1);
	cy = &cy_obj->item.cy;
	s.d[0] = v_dot(v_x(ray->dir, cy->norm), v_x(ray->dir, cy->norm));
	s.d[1] = 2 * v_dot(v_x(ray->dir, cy->norm), v_x(ray->orgn, cy->norm));
	s.d[2] = -2 * v_dot(v_x(ray->dir, cy->norm), v_x(cy->coord, cy->norm));
	s.d[4] = v_dot(v_x(cy->coord, cy->norm), v_x(cy->coord, cy->norm));
	s.d[5] = v_dot(v_x(ray->orgn, cy->norm), v_x(ray->orgn, cy->norm));
	s.d[6] = -2 * v_dot(v_x(ray->orgn, cy->norm),\
	v_x(cy->coord, cy->norm)) - pow(cy->diameter / 2, 2);
	solve_quadratic(s.d[0], s.d[1] + s.d[2], s.d[4] + s.d[5] + s.d[6], t);
	s.i = t->size;
	while (s.i > 0)
	{
		s.v[0] = v_add(ray->orgn, v_smult(ray->dir, t->arr[s.i - 1]));
		s.v[1] = v_sub(s.v[0], cy->coord);
		if (v_dot(s.v[1], cy->norm) > cy->h || v_dot(s.v[1], cy->norm) < 0)
			t->arr[s.i - 1] = MAX_DIST;
		s.i--;
	}
	selection_sort(t->arr, t->size);
	return (0);
}

static int		ray_intersect_caps(t_ray *ray, t_object *cy_obj, t_t *t)
{
	t_cy		*cy;
	t_ray_inter	s;

	cy = &cy_obj->item.cy;
	s.d[0] = v_dot(cy->norm, v_sub(cy->coord, ray->orgn));
	s.d[1] = v_dot(cy->norm, ray->dir);
	if (!isinf(s.d[2] = s.d[0] / s.d[1]))
	{
		s.v[0] = v_add(ray->orgn, v_smult(ray->dir, s.d[2]));
		s.v[1] = v_sub(s.v[0], cy->coord);
		if (v_norm(s.v[1]) <= cy->diameter / 2)
			t->arr[t->size++] = s.d[2];
	}
	s.d[0] = v_dot(cy->norm, v_sub(v_add(cy->coord,\
	v_smult(cy->norm, cy->h - 0.01)), ray->orgn));
	s.d[1] = v_dot(cy->norm, ray->dir);
	if (!isinf(s.d[2] = s.d[0] / s.d[1]))
	{
		s.v[0] = v_add(ray->orgn, v_smult(ray->dir, s.d[2]));
		s.v[1] = v_sub(s.v[0], v_add(cy->coord, v_smult(cy->norm, cy->h)));
		if (v_norm(s.v[1]) <= cy->diameter / 2)
			t->arr[t->size++] = s.d[2];
	}
	return (0);
}

int				ray_intersect_cy(t_ray *ray, t_object *cy_obj, t_t *t)
{
	if (!ray || ray_intersect_sausage(ray, cy_obj, t) ||
		ray_intersect_caps(ray, cy_obj, t))
		return (1);
	return (0);
}
