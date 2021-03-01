#include "miniRT.h"

t_v surface_vector_cy(t_intersect *inter, t_object *cy_obj)
{
	t_cy			*cy;
	double 			x;
	t_v 			xp;
	double 			k;

	cy = &cy_obj->item.cy;
	k = v_dot(v_subtract(inter->contact, cy->coord), cy->norm) / v_norm(v_subtract(inter->contact, cy->coord));
	x = ((cy->diameter / 2) * k) / sqrt(1 - pow(k, 2));
	xp = v_subtract(inter->contact, v_add(cy->coord, v_scalar_mult(cy->norm, x)));
	if (point_line_dist(cy->coord, v_add(cy->coord, v_scalar_mult(cy->norm, cy->height)),
					 inter->contact)
	< cy->diameter / 2 - EPS)
		return (cy->norm);
	return (v_normalize(xp));
}

t_v surface_vector(t_intersect *inter, t_object *obj)
{
	t_v n;

	n = v_create(0,0,0);
	if (obj->type & SP)
		n = v_normalize(v_subtract(inter->contact, obj->item.sp.coord));
	else if (obj->type & PL)
		n = obj->item.pl.norm;
	else if (obj->type & SQ)
		n = obj->item.sq.norm;
	else if (obj->type & CY)
		n = surface_vector_cy(inter, obj);
	else if (obj->type & TR)
		n = v_normalize(v_cross(v_subtract(obj->item.tr.p[0],obj->item.tr.p[1]), v_subtract(obj->item.tr.p[2],obj->item
		.tr.p[1])));
	return (n);
}
