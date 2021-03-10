/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths1.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 15:47:57 by pfelipa           #+#    #+#             */
/*   Updated: 2021/03/08 15:48:00 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS1_H
# define MATHS1_H

typedef struct		s_v
{
	double			v[3];
}					t_v;

typedef struct		s_m
{
	int				size[2];
	double			m[3][3];
}					t_m;

t_v					v_create(double x1, double x2, double x3);
t_v					v_add(t_v v1, t_v v2);
t_v					v_sub(t_v v1, t_v v2);
double				v_dot(t_v v1, t_v v2);
double				v_norm(t_v v);
t_v					v_smult(t_v v, double s);
t_v					v_normlz(t_v v);
t_v					v_x(t_v v1, t_v v2);
double				point_line_dist(t_v x0, t_v x1, t_v p);
void				cofactor(double num[3][3], double f);
t_v					v_mat_mul_vec(t_m m, t_v v);
t_m					v_mat_mul(t_m a1, t_m a2);
t_m					rotate_x(double alpha);
t_m					rotate_y(double beta);
double				abs_f(double i);
t_v					v_make(double x, double y, double z);
t_m					m_i(int n);
t_m					dir_to_rot_mat(t_v dir);
t_m					norm_to_rot_mat(t_v norm);
t_m					m_transpose(t_m m);
double				max_f(double a, double b);
double				min_f(double a, double b);
double				abs_f(double a);
double				bound(double num, double lower_b, double upper_b);
t_m					rotate_xyz(double pitch, double yaw,
					double roll, t_m basis);
t_v					get_component(t_m mat, int col);
t_v					v_mid(t_v v1, t_v v2);

#endif
