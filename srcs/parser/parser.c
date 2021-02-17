#include "miniRT.h"

static int 	process_line(char *line, t_scene *scene)
{
	char **split;

	/// need to check that too many arguments aren't given
	if ((split = ft_split(line, ' ')) && *split)      /// if line is empty or there is error, return value is the same - NULL
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
			process_l(++split, scene);
		}
		else if (!ft_strcmp(*split, "pl"))
		{
			process_pl(++split, scene);
		}
		else if (!ft_strcmp(*split, "sp"))
		{
			process_sp(++split, scene);
		}
		else if (!ft_strcmp(*split, "sq"))
		{
			process_sq(++split, scene);
		}
		else if (!ft_strcmp(*split, "cy"))
		{
			process_cy(++split, scene);
		}
		else if (!ft_strcmp(*split, "tr"))
		{
			process_tr(++split, scene);
		}
		else
		{
			// free 'split' using function that free's array's of strings (apply free function to all elements of an array) and exit app accordingly
		}
	}
	return (0);
}

int 		parse_rt(char *rt, t_scene *scene)
{
	int 	fd;
	int 	n;
	char 	*line;

	ft_bzero(scene, sizeof(t_scene)); // initializing structure values to zero
	if ((fd = open(rt, O_RDONLY)) < 0)
		error(NULL);
	while ((n = get_next_line(fd, &line)) > 0)
	{
		process_line(line, scene);
	}
	get_next_line(fd, &line);
	process_line(line, scene);
	if (n < 0)
		error(NULL); /// need to set errno accordingly (in gnl?)
}