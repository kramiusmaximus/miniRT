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
		error("Provide necessary arguments for Resolution.", scene);
	if (*args)
		error("Error parsing Resolution.", scene);
}

void process_a(char **args, t_scene *scene)
{
	char **rgb;

	scene->s = scene->s | 0b00000010;
	if (is_float(args) && is_color(args + 1))
	{
		scene->ambient.intensity = bound(ft_atof(*args++), 0, 1);
		scene->ambient.color = extract_color(*args++);
	}
	else
		error("Provide necessary arguments for Ambient.", scene);
	if (*args)
		error("Error parsing Ambient.", scene);
}

void process_c(char **args, t_scene *scene)
{
	t_camera 	*camera;
	t_listc		*node;

	if (!(camera = malloc(sizeof(t_camera))))
		error(NULL, scene);
	if (is_coord(args) && is_coord(args + 1) && is_float(args + 2))
	{
		camera->coord = extract_coord(*args++);
		camera->dir = extract_dir(*args++);
		camera->fov = bound(ft_atof(*args++), 0, 180);
	}
	else
		error("Provide necessary arguments for Ambient.", scene);
	if (*args || !(node = ft_lstcnew(camera)))
		error("Error parsing camera.", scene);
	camera->basis = obj_dir_transform(m_i(3), camera->dir);
	ft_lstcadd_front(&scene->camera, node);
}

void process_l(char **args, t_scene *scene)
{
	t_light *light;
	t_list *node;

	if (!(light = malloc(sizeof(t_light))))
		error(NULL, scene);
	if (is_coord(args) && is_float(args + 1) && is_color(args + 2))
	{
		light->coordinates = extract_coord(*args++);
		light->intensity = bound(ft_atof(*args++), 0, 1);
		light->color = extract_color(*args++);
	}
	else
		error("Provide necessary arguments for Light object.", scene);
	if (*args || !(node = ft_lstnew(light)))
		error("Object parsing error", scene);
	ft_lstadd_front(&scene->light, node);
}

void process_pl(char **args, t_scene *scene)
{
	t_object 	*pl_obj;
	t_list		*node;

	if (!(pl_obj = malloc(sizeof(t_object))))
		error(NULL, scene);
	pl_obj->type = PL;
	if (is_coord(args) && is_coord(args + 1) && is_color(args + 2))
	{
		pl_obj->item.pl.coord = extract_coord(*args++);
		pl_obj->item.pl.norm = extract_dir(*args++);
		pl_obj->color = extract_color(*args++);
	}
	else
		error("Provide necessary arguments for Plane object.", scene);
	if (is_float(args) && is_float(args + 1) && is_float(args + 2))
	{
		pl_obj->reflectivity = bound(ft_atof(*args++), 0, 1);
		pl_obj->transperancy = bound(ft_atof(*args++), 0, 1);
		pl_obj->refraction = max_f(ft_atof(*args++), 0);
	}
	if (*args || !(node = ft_lstnew(pl_obj)))
		error("Object parsing error", scene);
	ft_lstadd_front(&scene->object, node);
}
