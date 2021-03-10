/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_parsing2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 15:09:53 by pfelipa           #+#    #+#             */
/*   Updated: 2021/03/10 15:09:54 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	process_sp(char **args, t_scene *scene)
{
	t_object	*sp_obj;
	t_list		*node;

	node = NULL;
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
	args = norminette_can_eat_my_ass(sp_obj, args);
	if (*args || !(node = ft_lstnew(sp_obj)))
		error("Object parsing error", scene);
	ft_lstadd_front(&scene->object, node);
}

void	process_sq(char **args, t_scene *scene)
{
	t_object	*sq_obj;
	t_list		*node;

	node = NULL;
	if (!(sq_obj = malloc(sizeof(t_object))))
		error(NULL, scene);
	sq_obj->type = SQ;
	if (is_coord(args) && is_coord(args + 1)\
	&& is_float(args + 2) && is_color(args + 3))
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
	args = norminette_can_eat_my_ass(sq_obj, args);
	sq_obj->item.sq.basis = norm_to_rot_mat(sq_obj->item.sq.norm);
	if (*args || !(node = ft_lstnew(sq_obj)))
		error("Object parsing error", scene);
	ft_lstadd_front(&scene->object, node);
}

void	process_cy(char **args, t_scene *scene)
{
	t_object	*cy_obj;
	t_list		*node;

	node = NULL;
	if (!(cy_obj = malloc(sizeof(t_object))))
		error(NULL, scene);
	cy_obj->type = CY;
	if (is_coord(args) && is_coord(args + 1) && is_float(\
	args + 2) && is_float(args + 3) && is_color(args + 4))
	{
		cy_obj->item.cy.coord = extract_coord(*args++);
		cy_obj->item.cy.norm = extract_dir(*args++);
		cy_obj->item.cy.diameter = ft_atof(*args++);
		cy_obj->item.cy.h = ft_atof(*args++);
		if (!(cy_obj->item.cy.diameter && cy_obj->item.cy.h))
			error("Cylinder diameter and height have to be > 0", scene);
		cy_obj->color = extract_color(*args++);
	}
	else
		error("Provide necessary arguments for Cylinder object.", scene);
	args = norminette_can_eat_my_ass(cy_obj, args);
	if (*args || !(node = ft_lstnew(cy_obj)))
		error("Object parsing error", scene);
	ft_lstadd_front(&scene->object, node);
}

void	process_tr(char **args, t_scene *scene)
{
	t_object	*tr_obj;
	t_list		*node;

	node = NULL;
	if (!(tr_obj = malloc(sizeof(t_object))))
		error(NULL, scene);
	tr_obj->type = TR;
	if (is_coord(args) && is_coord(args + 1)\
	&& is_coord(args + 2) && is_color(args + 3))
	{
		tr_obj->item.tr.p[0] = extract_coord(*args++);
		tr_obj->item.tr.p[1] = extract_coord(*args++);
		tr_obj->item.tr.p[2] = extract_coord(*args++);
		tr_obj->color = extract_color(*args++);
	}
	else
		error("Provide necessary arguments for Triangle object.", scene);
	args = norminette_can_eat_my_ass(tr_obj, args);
	if (*args || !(node = ft_lstnew(tr_obj)))
		error("Object parsing error", scene);
	ft_lstadd_front(&scene->object, node);
}
