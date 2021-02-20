#include "miniRT.h"

int 		process_r(char **args, t_scene *scene)
{
	scene->s = scene->s | 0b00000001;
	if (is_int(args) && is_int(args + 1))
	{
		scene->res.width = ft_atoi(*args++);
		scene->res.height = ft_atoi(*args++);
	}
	if (*args)
		error("Too many arguments specified for resolution.", scene);
	return (0);
}

int 		process_a(char **args, t_scene *scene)
{
	char **rgb;

	scene->s = scene->s | 0b00000010;
	if (is_float(args))
		scene->ambient.intensity = bound(ft_atof(*args++), 0, 1);
	if (is_color(args))
	{
		rgb = ft_split(*args++, ',');
		scene->ambient.color = rgb_create(0, ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	}
	if (*args)
		error("Too many arguments specified for ambient light.", scene);
	return (0);
}

int 		process_c(char **args, t_scene *scene)
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
		dir = ft_split(*args++, ',');
		camera->dir = v_normalize(v_create(ft_atof(dir[0]), ft_atof(dir[1]), ft_atof(dir[2])));
	}
	if (is_float(args))
		camera->fov = bound(ft_atof(*args++), 0, 180);
	if (*args || !(node = ft_lstcnew(camera)))
		error("Too many arguments specified for camera or failed malloc", scene);
	camera->basis = m_i(3);
	camera->basis = cam_dir_transform(camera->basis, camera->dir);
	ft_lstcadd_front(&scene->camera, node);
}

int 		process_l(char **args, t_scene *scene)
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
		error("Too many arguments specified for light or failed malloc", scene);
	ft_lstadd_front(&scene->light, node);
}

int 		process_pl(char **args, t_scene *scene)
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
		error("Too many arguments specified for plane object or failed malloc", scene);
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
	if (is_coord(args) && is_coord(args + 1))
	{
		coord = ft_split(*args++, ',');
		sp_obj->item.sp.coord = v_create(ft_atof(coord[0]), ft_atof(coord[1]), ft_atof(coord[2]));
	}
	if (is_float(args))
	{
		sp_obj->item.sp.diameter = ft_atof(*args++);
		if (sp_obj->item.sp.diameter <= 0)
		{
			free(sp_obj);
			return ;
		}
	}
	if (is_color(args))
	{
		rgb = ft_split(*args++, ',');
		sp_obj->color = rgb_create(0, ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	}
	if (is_float(args))
		sp_obj->reflectivity = bound(ft_atof(*args++), 0, 1);
	if (is_float(args) && is_float(args + 1))
	{
		sp_obj->transperancy = bound(ft_atof(*args++), 0, 1);
		sp_obj->refraction = ft_atof(*args++);
		// need to make sure refraction index is within bound (what are the bound?)
	}
	if (*args || !(node = ft_lstnew(sp_obj)))
		error("Too many arguments specified for sphere object or failed malloc", scene);
	ft_lstadd_front(&scene->object, node);
}

int 		process_sq(char **args, t_scene *scene)
{
	char 		**coord;
	char 		**norm;
	char 		**rgb;
	t_object 	*sq_obj;
	t_list		*node;

	if (!(sq_obj = malloc(sizeof(t_object))))
	{} /// process error
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
		{} /// process error
	}
	if (is_color(args))
	{
		rgb = ft_split(*args++, ',');
		sq_obj->color = rgb_create(0, ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	}
	if (is_float(args))
	{
		sq_obj->reflectivity = ft_atof(*args++);
		sq_obj->reflectivity = sq_obj->reflectivity > 1 ? 1 : sq_obj->reflectivity;
		sq_obj->reflectivity = sq_obj->reflectivity < 0 ? 0 : sq_obj->reflectivity;
	}
	if (is_float(args) && is_float(args + 1))
	{
		sq_obj->transperancy = ft_atof(*args++);
		sq_obj->transperancy = sq_obj->transperancy > 1 ? 1 : sq_obj->transperancy;
		sq_obj->transperancy = sq_obj->transperancy < 0 ? 0 : sq_obj->transperancy;
		sq_obj->refraction = ft_atof(*args++);
		// need to make sure refraction index is within bound (what are the bound?)
	}
	if (*args || !(node = ft_lstnew(sq_obj)))
	{} /// process error
	ft_lstadd_front(&scene->object, node);
}

int 		process_cy(char **args, t_scene *scene)
{
	char 		**coord;
	char 		**norm;
	char 		**rgb;
	t_object 	*cy_obj;
	t_list		*node;

	if (!(cy_obj = malloc(sizeof(t_object))))
	{} /// process error
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
		/// make sure both parameters are above 0 or object is ignored
	}
	if (is_color(args))
	{
		rgb = ft_split(*args++, ',');
		cy_obj->color = rgb_create(0, ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	}
	if (is_float(args))
	{
		cy_obj->reflectivity = ft_atof(*args++);
		cy_obj->reflectivity = cy_obj->reflectivity > 1 ? 1 : cy_obj->reflectivity;
		cy_obj->reflectivity = cy_obj->reflectivity < 0 ? 0 : cy_obj->reflectivity;
	}
	if (is_float(args) && is_float(args + 1))
	{
		cy_obj->transperancy = ft_atof(*args++);
		cy_obj->transperancy = cy_obj->transperancy > 1 ? 1 : cy_obj->transperancy;
		cy_obj->transperancy = cy_obj->transperancy < 0 ? 0 : cy_obj->transperancy;
		cy_obj->refraction = ft_atof(*args++);
		// need to make sure refraction index is within bound (what are the bound?)
	}
	if (*args || !(node = ft_lstnew(cy_obj)))
	{} /// process error
	ft_lstadd_front(&scene->object, node);
}

int 		process_tr(char **args, t_scene *scene)
{
	char 		**coord[3];
	char 		**rgb;
	t_object 	*tr_obj;
	t_list		*node;

	if (!(tr_obj = malloc(sizeof(t_object))))
	{} /// process error
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
	{
		tr_obj->reflectivity = ft_atof(*args++);
		tr_obj->reflectivity = tr_obj->reflectivity > 1 ? 1 : tr_obj->reflectivity;
		tr_obj->reflectivity = tr_obj->reflectivity < 0 ? 0 : tr_obj->reflectivity;
	}
	if (is_float(args) && is_float(args + 1))
	{
		tr_obj->transperancy = ft_atof(*args++);
		tr_obj->transperancy = tr_obj->transperancy > 1 ? 1 : tr_obj->transperancy;
		tr_obj->transperancy = tr_obj->transperancy < 0 ? 0 : tr_obj->transperancy;
		tr_obj->refraction = ft_atof(*args++);
		// need to make sure refraction index is within bound (what are the bound?)
	}
	if (*args || !(node = ft_lstnew(tr_obj)))
	{} /// process error
	ft_lstadd_front(&scene->object, node);
}