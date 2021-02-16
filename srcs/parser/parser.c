#include "miniRT.h"

int 		process_r(char **args, t_scene *scene)
{
	if (!(*args && is_int(*args) && *(args + 1) && is_int(*(args + 1))))
	{} /// process error
	scene->window_dims.width = ft_atoi(*args++);
	scene->window_dims.height = ft_atoi(*args);
	return (0);
}

int 		process_a(char **args, t_scene *scene)
{
	int *rgb;

	if (!(*args && is_float(*args) && *(args + 1) && is_input_color(*(args + 1))))
	{} /// process error
	if ((scene->ambient.intensity = ft_atof(*args++)) < 0 || scene->ambient.intensity > 1)
	{} /// process error
	rgb = ft_split(*args, ',');
	scene->ambient.color = rgb_create(0, rgb[0], rgb[1], rgb[2]);
	return (0);
}

int 		process_c(char **args, t_scene *scene)
{

}

static int process_line(char *line, t_scene *scene)
{
	char **split;

	if (!(split = ft_split(line, ' ')))      /// if line is empty or there is error, return value is the same - NULL
	{
		if (!ft_strcmp(*split, "R"))
		{
			process_r(++split, scene);
		}
		else if (!ft_strcmp(*split, "A"))
		{
			process_a(++split, scene);
		}
		else if (!ft_strcmp(*split, "c"))
		{
			process_c(++split, scene);
		}
		else if (!ft_strcmp(*split, "l"))
		{
			//process_l(++split);
		}
		else if (!ft_strcmp(*split, "pl"))
		{
			//process_pl(++split);
		}
		else if (!ft_strcmp(*split, "sp"))
		{
			//process_sp(++split);
		}
		else if (!ft_strcmp(*split, "sq"))
		{
			//process_sq(++split);
		}
		else if (!ft_strcmp(*split, "cy"))
		{
			//process_cy(++split);
		}
		else if (!ft_strcmp(*split, "tr"))
		{
			//process_tr(++split);
		}
		else
		{
			// free 'split' using function that free's array's of strings (apply free function to all elements of an array) and exit app accordingly
		}
	}
	return (0);
}

int parse_rt(char *rt, t_scene *scene)
{
	int 	fd;
	int 	n;
	char 	*line;

	ft_bzero(scene, sizeof(t_scene)); // initializing structure values to zero
	if ((fd = open(rt, O_RDONLY) < 0))
		error(NULL);
	while ((n = get_next_line(fd, &line)) > 0)
	{
		process_line(line, &scene);
	}
	if (n < 0)
		error(NULL); /// need to set errno accordingly (in gnl?)
}