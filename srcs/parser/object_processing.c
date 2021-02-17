#include "miniRT.h"

int 		process_r(char **args, t_scene *scene)
{
	if (!(*args && is_int(*args) && *(args + 1) && is_int(*(args + 1))))
	{} /// process error
	scene->res.width = ft_atoi(*args++);
	scene->res.height = ft_atoi(*args++);
	if (*args)
	{} /// process error
	return (0);
}

int 		process_a(char **args, t_scene *scene)
{
	char **rgb;

	if (!(*args && is_float(*args) && *(args + 1) && is_input_color(*(args + 1))))
	{} /// process error
	scene->ambient.intensity = ft_atof(*args++);
	if (scene->ambient.intensity < 0 || scene->ambient.intensity > 1)
	{} /// process error
	rgb = ft_split(*args++, ',');
	scene->ambient.color = rgb_create(0, ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	return (0);
}

int 		process_c(char **args, t_scene *scene)
{
	char 		**coord;
	char 		**dir;
	t_camera 	*camera;
	t_listc		*node;

	if (!(camera = malloc(sizeof(t_camera))))
	{}	/// process error
	if (!(*args && is_coords(*args) && *(args + 1) && is_coords(*(args + 1)) && *(args + 2) && is_float(*(args + 2))))
	{} /// process error
	coord = ft_split(*args++, ',');
	camera->coordinates = v_create(ft_atof(coord[0]), ft_atof(coord[1]), ft_atof(coord[2]));
	dir = ft_split(*args++, ',');
	camera->dir = v_create(ft_atof(dir[0]), ft_atof(dir[1]), ft_atof(dir[2]));
	camera->fov = ft_atof(*args++);
	if (camera->fov < 0 || camera->fov > 180)
	{} /// process error
	if (*args || !(node = ft_lstcnew(camera)))
	{} /// process error
	ft_lstcadd_front(&scene->camera, node);
}

int 		process_l(char **args, t_scene *scene)
{
	char **coord;
	char **rgb;
	t_light *light;
	t_list *node;

	if (!(light = malloc(sizeof(t_light))))
	{} /// process error
	if (!(*args && is_coords(*args) && *(args + 1) && is_float(*(args + 1)) && *(args + 2) && is_input_color(*(args + 2))))
	{} /// process error
	coord = ft_split(*args++, ',');
	light->coordinates = v_create(ft_atof(coord[0]), ft_atof(coord[1]), ft_atof(coord[2]));
	light->intensity = ft_atof(*args++);
	if (light->intensity < 0 || light->intensity > 1)
	{} /// process error
	rgb = ft_split(*args++, ',');
	light->color = rgb_create(0, ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	if (*args || !(node = ft_lstnew(light)))
	{} /// process error
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
	{} /// process error
	if (!(*args && is_coords(*args) && *(args + 1) && is_coords(*(args + 1)) && *(args + 2) && is_input_color(*(args + 2))))
	{} /// process error
	pl_obj->type = PL;
	coord = ft_split(*args++, ',');
	pl_obj->item.pl.coord = v_create(ft_atof(coord[0]), ft_atof(coord[1]), ft_atof(coord[2]));
	norm = ft_split(*args++, ',');
	pl_obj->item.pl.norm = v_normalize(v_create(ft_atof(norm[0]), ft_atof(norm[1]), ft_atof(norm[2])));
	rgb = ft_split(*args++, ',');
	pl_obj->color = rgb_create(0, ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	if (*args || !(node = ft_lstnew(pl_obj)))
	{} /// process error
	ft_lstadd_front(&scene->object, node);
}

int 		process_sp(char **args, t_scene *scene)
{
	char 		**coord;
	char 		**rgb;
	t_object 	*sp_obj;
	t_list		*node;

	if (!(sp_obj = malloc(sizeof(t_object))))
	{} /// process error
	if (!(*args && is_coords(*args) && *(args + 1) && is_float(*(args + 1)) && *(args + 2) && is_float(*(args + 2)) && *(args + 3) && is_input_color(*(args + 3))))
	{} /// process error
	sp_obj->type = SP;
	coord = ft_split(*args++, ',');
	sp_obj->item.sp.coord = v_create(ft_atof(coord[0]), ft_atof(coord[1]), ft_atof(coord[2]));
	sp_obj->item.sp.diameter = ft_atof(*args++);
	if (sp_obj->item.sp.diameter <= 0)
	{} /// process error
	sp_obj->reflectivity = ft_atof(*args++);
	if (sp_obj->reflectivity > 1 || sp_obj->reflectivity < 0)
	{} /// process error
	rgb = ft_split(*args++, ',');
	sp_obj->color = rgb_create(0, ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	if (*args || !(node = ft_lstnew(sp_obj)))
	{} /// process error
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
	if (!(*args && is_coords(*args) && *(args + 1) && is_coords(*(args + 1)) && *(args + 2) && is_float(*(args + 2)) && *(args + 3) && is_input_color(*(args + 3))))
	{} /// process error
	sq_obj->type = SQ;
	coord = ft_split(*args++, ',');
	sq_obj->item.sq.coord = v_create(ft_atof(coord[0]), ft_atof(coord[1]), ft_atof(coord[2]));
	norm = ft_split(*args++, ',');
	sq_obj->item.sq.norm = v_normalize(v_create(ft_atof(norm[0]), ft_atof(norm[1]), ft_atof(norm[2])));
	sq_obj->item.sq.side_len = ft_atof(*args++);
	rgb = ft_split(*args++, ',');
	sq_obj->color = rgb_create(0, ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
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
	if (!(*args && is_coords(*args) && *(args + 1) && is_coords(*(args + 1)) && *(args + 2) && is_float(*(args + 2)) && *(args + 3) && is_float(*(args + 3)) && *(args + 4) && is_input_color(*(args + 4))))
	{} /// process error
	cy_obj->type = CY;
	coord = ft_split(*args++, ',');
	cy_obj->item.cy.coord = v_create(ft_atof(coord[0]), ft_atof(coord[1]), ft_atof(coord[2]));
	norm = ft_split(*args++, ',');
	cy_obj->item.cy.norm = v_normalize(v_create(ft_atof(norm[0]), ft_atof(norm[1]), ft_atof(norm[2])));
	cy_obj->item.cy.diameter = ft_atof(*args++);
	cy_obj->item.cy.height = ft_atof(*args++);
	rgb = ft_split(*args++, ',');
	cy_obj->color = rgb_create(0, ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
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
	if (!(*args && is_coords(*args) && *(args + 1) && is_coords(*(args + 1)) && *(args + 2) && is_coords(*(args + 2)) && *(args + 3) && is_input_color(*(args + 3))))
	{} /// process error
	tr_obj->type = TR;
	coord[0] = ft_split(*args++, ',');
	tr_obj->item.tr.p[0] = v_create(ft_atof(coord[0][0]), ft_atof(coord[0][1]), ft_atof(coord[0][2]));
	coord[1] = ft_split(*args++, ',');
	tr_obj->item.tr.p[1] = v_create(ft_atof(coord[1][0]), ft_atof(coord[1][1]), ft_atof(coord[1][2]));
	coord[2] = ft_split(*args++, ',');
	tr_obj->item.tr.p[2] = v_create(ft_atof(coord[2][0]), ft_atof(coord[2][1]), ft_atof(coord[2][2]));
	rgb = ft_split(*args++, ',');
	tr_obj->color = rgb_create(0, ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	if (*args || !(node = ft_lstnew(tr_obj)))
	{} /// process error
	ft_lstadd_front(&scene->object, node);
}