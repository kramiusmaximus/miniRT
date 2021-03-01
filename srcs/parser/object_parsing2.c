#include "miniRT.h"

void process_sp(char **args, t_scene *scene)
{
	t_object 	*sp_obj;
	t_list		*node;

	if (!(sp_obj = malloc(sizeof(t_object))))
		error(NULL, scene);
	sp_obj->type = SP;
	if (is_coord(args) && is_float(args + 1) && is_color(args + 2))
	{
		sp_obj->item.sp.coord = extract_coord(*args++);
		sp_obj->item.sp.diameter = ft_atof(*args++);
		if (sp_obj->item.sp.diameter <= 0)
			error("Sphere diameter has to be > 0", scene);
		sp_obj->color = extract_color(*args++);
	}
	else
		error("Provide necessary arguments for Sphere object.", scene);
	if (is_float(args) && is_float(args + 1) && is_float(args + 2))
	{
		sp_obj->reflectivity = bound(ft_atof(*args++), 0, 1);
		sp_obj->transperancy = bound(ft_atof(*args++), 0, 1);
		sp_obj->refraction = max_f(ft_atof(*args++), 0);
	}
	if (*args || !(node = ft_lstnew(sp_obj)))
		error("Object parsing error", scene);
	ft_lstadd_front(&scene->object, node);
}

void process_sq(char **args, t_scene *scene)
{
	t_object 	*sq_obj;
	t_list		*node;

	if (!(sq_obj = malloc(sizeof(t_object))))
		error(NULL, scene);
	sq_obj->type = SQ;
	if (is_coord(args) && is_coord(args + 1) && is_float(args + 2) && is_color(args + 3))
	{
		sq_obj->item.sq.coord = extract_coord(*args++);
		sq_obj->item.sq.norm = extract_dir(*args++);
		sq_obj->item.sq.side_len = ft_atof(*args++);
		if (sq_obj->item.sq.side_len < 0)
			error("Square length has to be > 0", scene);
		sq_obj->color = extract_color(*args++);
	}
	else
		error("Provide necessary arguments for Square object.", scene);
	if (is_float(args) && is_float(args + 1) && is_float(args + 2))
	{
		sq_obj->reflectivity = bound(ft_atof(*args++), 0, 1);
		sq_obj->transperancy = bound(ft_atof(*args++), 0, 1);
		sq_obj->refraction = max_f(ft_atof(*args++), 0);
	}
	sq_obj->item.sq.basis = obj_norm_transform(m_i(3), sq_obj->item.sq.norm);
	if (*args || !(node = ft_lstnew(sq_obj)))
		error("Object parsing error", scene);
	ft_lstadd_front(&scene->object, node);
}

void process_cy(char **args, t_scene *scene)
{
	t_object 	*cy_obj;
	t_list		*node;

	if (!(cy_obj = malloc(sizeof(t_object))))
		error(NULL, scene);
	cy_obj->type = CY;
	if (is_coord(args) && is_coord(args + 1) && is_float(args + 2) && is_float(args + 3) && is_color(args + 4))
	{
		cy_obj->item.cy.coord = extract_coord(*args++);
		cy_obj->item.cy.norm = extract_dir(*args++);
		cy_obj->item.cy.diameter = ft_atof(*args++);
		cy_obj->item.cy.height = ft_atof(*args++);
		if (!(cy_obj->item.cy.diameter && cy_obj->item.cy.height))
			error("Cylinder diameter and height have to be > 0", scene);
		cy_obj->color = extract_color(*args++);
	}
	else
		error("Provide necessary arguments for Cylinder object.", scene);
	if (is_float(args) && is_float(args + 1) && is_float(args + 2))
	{
		cy_obj->reflectivity = bound(ft_atof(*args++), 0, 1);
		cy_obj->transperancy = bound(ft_atof(*args++), 0, 1);
		cy_obj->refraction = max_f(ft_atof(*args++), 0);
	}
	if (*args || !(node = ft_lstnew(cy_obj)))
		error("Object parsing error", scene);
	ft_lstadd_front(&scene->object, node);
}

int 		process_tr(char **args, t_scene *scene)
{
	t_object *tr_obj;
	t_list *node;

	if (!(tr_obj = malloc(sizeof(t_object))))
		error(NULL, scene);
	tr_obj->type = TR;
	if (is_coord(args) && is_coord(args + 1) && is_coord(args + 2) && is_color(args + 4))
	{
		tr_obj->item.tr.p[0] = extract_coord(*args++);
		tr_obj->item.tr.p[1] = extract_coord(*args++);
		tr_obj->item.tr.p[2] = extract_coord(*args++);
		tr_obj->color = extract_color(*args++);
	} else
		error("Provide necessary arguments for Triangle object.", scene);
	if (is_float(args) && is_float(args + 1) && is_float(args + 2))
	{
		tr_obj->reflectivity = bound(ft_atof(*args++), 0, 1);
		tr_obj->transperancy = bound(ft_atof(*args++), 0, 1);
		tr_obj->refraction = ft_atof(*args++);
	}
	if (*args || !(node = ft_lstnew(tr_obj)))
		error("Object parsing error", scene);
	ft_lstadd_front(&scene->object, node);
}
