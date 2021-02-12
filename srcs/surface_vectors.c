#include "miniRT.h"

t_v surface_vector_cy(t_ray *ray, t_intersect *inter, t_object *obj)							// can rewrite this so that unnecessary computations arent made
{
	t_cy			cy;
	t_v 			n;
	t_v 			op;
	double 			x;
	t_v 			xp;
	double 			k;

	cy = obj->data.cy;
	op = v_subtract(inter->contact, cy.coordinates);
	k = v_dot(op, cy.normal) / v_norm(op);
	x = ((cy.diameter / 2) * k) / sqrt(1 - pow(k, 2));
	xp = v_subtract(inter->contact, v_add(cy.coordinates, v_scalar_mult(cy.normal, x)));
	k = v_norm(xp);
	if (point_line_dist(cy.coordinates, v_add(cy.coordinates, v_scalar_mult(cy.normal, cy.height)), inter->contact) < cy.diameter / 2 - 0.0000001)
		return (cy.normal);
	return (v_normalize(xp));
}

t_v surface_vector(t_ray *ray, t_intersect *inter, t_object *obj)
{
	t_v n = {0, 0, 0};
	t_cy	cy;
	double 	d;

	// what if we're inside?
	if (obj->type & SP)
		n = v_normalize(v_subtract(inter->contact, obj->data.sp.coordinates));
	else if (obj->type & PL)
		n = obj->data.pl.normal;
	else if (obj->type & SQ)
		n = obj->data.sq.top;
	else if (obj->type & CY)
		n = surface_vector_cy(ray, inter, obj);
	else if (obj->type & TR)
	{}
	return (n);
}
