#ifndef VECTORS_H
# define VECTORS_H
typedef struct		s_v
{
	double 			v[3];
}					t_v;

typedef struct		s_3dmat
{
	double 			m[3][3];
}					t_3dmat;

t_v 				v_create(double x1, double x2, double x3);
t_v					v_add(t_v v1, t_v v2);
t_v					v_subtract(t_v v1, t_v v2);
double				v_dot(t_v v1, t_v v2);
double 				v_norm(t_v v);
t_v 				v_scalar_mult(t_v v, double s);
t_v 				v_normalize(t_v v);
t_v 				v_random(t_v v, double amount);
t_v 				v_cross(t_v v1, t_v v2);
double				point_line_dist(t_v x0, t_v x1, t_v p);

#endif
