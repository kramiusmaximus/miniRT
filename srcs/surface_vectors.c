#include "miniRT.h"

t_v surface_vector(t_ray *ray, t_object *obj, t_intersect *inter)
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
	{
		cy = obj->data.cy;
		d = point_line_dist(cy.coordinates, v_add(cy.coordinates, v_scalar_mult(cy.normal, cy.height)), inter->contact);
		if (d < cy.diameter / 2 - 0.0001)
			n = cy.normal;
	}
	else if (obj->type & TR)
	{}
	return (n);
}
