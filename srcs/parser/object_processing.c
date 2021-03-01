#include "miniRT.h"

void process_r(char **args, t_scene *scene)
{
	scene->s = scene->s | 0b00000001;
	if (is_int(args) && is_int(args + 1))
	{
		scene->res.width = ft_atoi(*args++);
		scene->res.height = ft_atoi(*args++);
	}
	else
		error("Provide necessary arguments for resolution", scene);
	if (*args)
		error("Error parsing resolution.", scene);
}

void process_a(char **args, t_scene *scene)
{
	char **rgb;

	scene->s = scene->s | 0b00000010;
	if (is_float(args))
		scene->ambient.intensity = bound(ft_atof(*args++), 0, 1);
	if (is_color(args))
	{
		rgb = ft_split(*args++, ',');
		scene->ambient.color = rgb_create(0, ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
		// scene->ambient.color = extract_color(char **args);
	}
	if (*args)
		error("Error parsing ambient.", scene);
}

void process_c(char **args, t_scene *scene)
{
	char 		**coord;
	char 		**dir;
	t_camera 	*camera;
	t_listc		*node;

	if (!(camera = malloc(sizeof(t_camera))))
		error(NULL, scene);
	if (is_coord(args) && is_coord(args + 1))
	{
		coord = ft_split(*args++, ',');
		camera->coord = v_create(ft_atof(coord[0]), ft_atof(coord[1]), ft_atof(coord[2]));
		// camera->coord = extract_coord(char **args);
		dir = ft_split(*args++, ',');
		camera->dir = v_normalize(v_create(ft_atof(dir[0]), ft_atof(dir[1]), ft_atof(dir[2])));
		// camera->dir = extract_dir(char **args);
	}
	if (is_float(args))
		camera->fov = bound(ft_atof(*args++), 0, 180);
	if (*args || !(node = ft_lstcnew(camera)))
		error("Error parsing camera.", scene);
	camera->basis = m_i(3);
	camera->basis = obj_dir_transform(camera->basis, camera->dir);
	ft_lstcadd_front(&scene->camera, node);
}

void process_l(char **args, t_scene *scene)
{
	char **coord;
	char **rgb;
	t_light *light;
	t_list *node;

	if (!(light = malloc(sizeof(t_light))))
		error(NULL, scene);
	if (is_coord(args))
	{
		coord = ft_split(*args++, ',');
		light->coordinates = v_create(ft_atof(coord[0]), ft_atof(coord[1]), ft_atof(coord[2]));
	}
	if (is_float(args))
		light->intensity = bound(ft_atof(*args++), 0, 1);
	if (is_color(args))
	{
		rgb = ft_split(*args++, ',');
		light->color = rgb_create(0, ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	}
	if (*args || !(node = ft_lstnew(light)))
		error("Object parsing error", scene);
	ft_lstadd_front(&scene->light, node);
}

void process_pl(char **args, t_scene *scene)
{
	char 		**coord;
	char 		**norm;
	char 		**rgb;
	t_object 	*pl_obj;
	t_list		*node;

	if (!(pl_obj = malloc(sizeof(t_object))))
		error(NULL, scene);
	pl_obj->type = PL;
	if (is_coord(args) && is_coord(args + 1))
	{
		coord = ft_split(*args++, ',');
		pl_obj->item.pl.coord = v_create(ft_atof(coord[0]), ft_atof(coord[1]), ft_atof(coord[2]));
		norm = ft_split(*args++, ',');
		pl_obj->item.pl.norm = v_normalize(v_create(ft_atof(norm[0]), ft_atof(norm[1]), ft_atof(norm[2])));
	}
	if (is_color(args))
	{
		rgb = ft_split(*args++, ',');
		pl_obj->color = rgb_create(0, ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	}
	if (is_float(args))
		pl_obj->reflectivity = bound(ft_atof(*args++), 0, 1);
	if (is_float(args) && is_float(args + 1))
	{
		pl_obj->transperancy = bound(ft_atof(*args++), 0, 1);
		pl_obj->refraction = ft_atof(*args++);
		// need to make sure refraction index is within bound (what are the bound?)
	}
	if (*args || !(node = ft_lstnew(pl_obj)))
		error("Object parsing error", scene);
	ft_lstadd_front(&scene->object, node);
}

void process_sp(char **args, t_scene *scene)
{
	char 		**coord;
	char 		**rgb;
	t_object 	*sp_obj;
	t_list		*node;

	if (!(sp_obj = malloc(sizeof(t_object))))
		error(NULL, scene);
	sp_obj->type = SP;
	if (is_coord(args) && is_float(args + 1) && is_color(args + 2))
	{
		coord = ft_split(*args++, ',');
		sp_obj->item.sp.coord = v_create(ft_atof(coord[0]), ft_atof(coord[1]), ft_atof(coord[2]));
		sp_obj->item.sp.diameter = ft_atof(*args++);
		if (sp_obj->item.sp.diameter <= 0)
		{
			free(sp_obj);
			return ;
		}
		rgb = ft_split(*args++, ',');
		sp_obj->color = rgb_create(0, ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	}
	if (is_float(args))
		sp_obj->reflectivity = bound(ft_atof(*args++), 0, 1);
	if (is_float(args) && is_float(args + 1))
	{
		sp_obj->transperancy = bound(ft_atof(*args++), 0, 1);
		sp_obj->refraction = max_f(ft_atof(*args++), 0);
	}
	if (*args || !(node = ft_lstnew(sp_obj)))
		error("Object parsing error", scene);
	ft_lstadd_front(&scene->object, node);
}

void process_sq(char **args, t_scene *scene)
{
	char 		**coord;
	char 		**norm;
	char 		**rgb;
	t_object 	*sq_obj;
	t_list		*node;

	if (!(sq_obj = malloc(sizeof(t_object))))
		error(NULL, scene);
	sq_obj->type = SQ;
	if (is_coord(args) && is_coord(args + 1))
	{
		coord = ft_split(*args++, ',');
		sq_obj->item.sq.coord = v_create(ft_atof(coord[0]), ft_atof(coord[1]), ft_atof(coord[2]));
		norm = ft_split(*args++, ',');
		sq_obj->item.sq.norm = v_normalize(v_create(ft_atof(norm[0]), ft_atof(norm[1]), ft_atof(norm[2])));
	}
	if (is_float(args))
	{
		sq_obj->item.sq.side_len = ft_atof(*args++);
		if (sq_obj->item.sq.side_len < 0)
		{
			free(sq_obj);
			return ;
		}
	}
	if (is_color(args))
	{
		rgb = ft_split(*args++, ',');
		sq_obj->color = rgb_create(0, ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	}
	if (is_float(args))
		sq_obj->reflectivity = bound(ft_atof(*args++), 0, 1);
	if (is_float(args) && is_float(args + 1))
	{
		sq_obj->transperancy = bound(ft_atof(*args++), 0, 1);
		sq_obj->refraction = ft_atof(*args++);
		// need to make sure refraction index is within bound (what are the bound?)
	}
	sq_obj->item.sq.basis = m_i(3);
	sq_obj->item.sq.basis = obj_norm_transform(sq_obj->item.sq.basis, sq_obj->item.sq.norm);
	if (*args || !(node = ft_lstnew(sq_obj)))
		error("Object parsing error", scene);
	ft_lstadd_front(&scene->object, node);
}

void process_cy(char **args, t_scene *scene)
{
	char 		**coord;
	char 		**norm;
	char 		**rgb;
	t_object 	*cy_obj;
	t_list		*node;

	if (!(cy_obj = malloc(sizeof(t_object))))
		error(NULL, scene);
	cy_obj->type = CY;
	if (is_coord(args) && is_coord(args + 1))
	{
		coord = ft_split(*args++, ',');
		cy_obj->item.cy.coord = v_create(ft_atof(coord[0]), ft_atof(coord[1]), ft_atof(coord[2]));
		norm = ft_split(*args++, ',');
		cy_obj->item.cy.norm = v_normalize(v_create(ft_atof(norm[0]), ft_atof(norm[1]), ft_atof(norm[2])));
	}
	if (is_float(args) && is_float(args + 1))
	{
		cy_obj->item.cy.diameter = ft_atof(*args++);
		cy_obj->item.cy.height = ft_atof(*args++);
		if (!(cy_obj->item.cy.diameter && cy_obj->item.cy.diameter))
		{
			free(cy_obj);
			return ;
		}
	}
	if (is_color(args))
	{
		rgb = ft_split(*args++, ',');
		cy_obj->color = rgb_create(0, ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	}
	if (is_float(args))
		cy_obj->reflectivity = bound(ft_atof(*args++), 0, 1);
	if (is_float(args) && is_float(args + 1))
	{
		cy_obj->transperancy = bound(ft_atof(*args++), 0, 1);
		cy_obj->refraction = ft_atof(*args++);
		// need to make sure refraction index is within bound (what are the bound?)
	}
	if (*args || !(node = ft_lstnew(cy_obj)))
		error("Object parsing error", scene);
	ft_lstadd_front(&scene->object, node);
}

int 		process_tr(char **args, t_scene *scene)
{
	char 		**coord[3];
	char 		**rgb;
	t_object 	*tr_obj;
	t_list		*node;

	if (!(tr_obj = malloc(sizeof(t_object))))
		error(NULL, scene);
	tr_obj->type = TR;
	if (is_coord(args) && is_coord(args + 1) && is_coord(args + 2))
	{
		coord[0] = ft_split(*args++, ',');
		tr_obj->item.tr.p[0] = v_create(ft_atof(coord[0][0]), ft_atof(coord[0][1]), ft_atof(coord[0][2]));
		coord[1] = ft_split(*args++, ',');
		tr_obj->item.tr.p[1] = v_create(ft_atof(coord[1][0]), ft_atof(coord[1][1]), ft_atof(coord[1][2]));
		coord[2] = ft_split(*args++, ',');
		tr_obj->item.tr.p[2] = v_create(ft_atof(coord[2][0]), ft_atof(coord[2][1]), ft_atof(coord[2][2]));
	}
	if (is_color(args))
	{
		rgb = ft_split(*args++, ',');
		tr_obj->color = rgb_create(0, ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	}
	if (is_float(args))
		tr_obj->reflectivity = bound(ft_atof(*args++), 0, 1);
	if (is_float(args) && is_float(args + 1))
	{
		tr_obj->transperancy = bound(ft_atof(*args++), 0, 1);
		tr_obj->refraction = ft_atof(*args++);
		tr_obj->item.sq.norm = get_component(tr_obj->item.sq.basis, 1);
		// need to make sure refraction index is within bound (what are the bound?)
	}
	if (*args || !(node = ft_lstnew(tr_obj)))
		error("Object parsing error", scene);
	ft_lstadd_front(&scene->object, node);
}