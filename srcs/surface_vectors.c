#include "miniRT.h"

t_v surface_vector_cy(t_ray *ray, t_intersect *inter, t_object *cy_obj)							// can rewrite this so that unnecessary computations arent made
{
	t_cy			*cy;
	t_v 			n;
	t_v 			op;
	double 			x;
	t_v 			xp;
	double 			k;

	cy = cy_obj->item.cy;
	op = v_subtract(inter->contact, cy_obj->coordinates);
	k = v_dot(op, cy->normal) / v_norm(op);
	x = ((cy->diameter / 2) * k) / sqrt(1 - pow(k, 2));
	xp = v_subtract(inter->contact, v_add(cy_obj->coordinates, v_scalar_mult(cy->normal, x)));
	if (point_line_dist(cy_obj->coordinates, v_add(cy_obj->coordinates, v_scalar_mult(cy->normal, cy->height)),
					 inter->contact)
	< cy->diameter / 2 - 0.0000001)
		return (cy->normal);
	return (v_normalize(xp));
}

t_v surface_vector(t_ray *ray, t_intersect *inter, t_object *obj)
{
	t_v n = {0, 0, 0};
	t_cy	cy;
	double 	d;

	// what if we're inside?
	if (obj->type & SP)
		n = v_normalize(v_subtract(inter->contact, obj->coordinates));
	else if (obj->type & PL)
		n = obj->item.pl->normal;
	else if (obj->type & SQ)
		n = obj->item.sq->top;
	else if (obj->type & CY)
		n = surface_vector_cy(ray, inter, obj);
	else if (obj->type & TR)
		n = v_cross(v_subtract(obj->item.tr->p[0],obj->item.tr->p[1]), v_subtract(obj->item.tr->p[2],obj->item
		.tr->p[1]));
	return (n);
}
