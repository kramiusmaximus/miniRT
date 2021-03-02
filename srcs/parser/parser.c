#include "miniRT.h"

static void process_line(char *line, t_scene *scene)
{
	char **split;

	if ((split = ft_split(line, ' ')) && *split)      /// if line is empty or there is error, return value is the same - NULL
	{
		if (!ft_strcmp(*split, "R") && !(scene->s & 0b00000001))
			process_r(++split, scene);
		else if (!ft_strcmp(*split, "A") && !(scene->s & 0b00000010))
			process_a(++split, scene);
		else if (!ft_strcmp(*split, "c"))
			process_c(++split, scene);
		else if (!ft_strcmp(*split, "l"))
			process_l(++split, scene);
		else if (!ft_strcmp(*split, "pl"))
			process_pl(++split, scene);
		else if (!ft_strcmp(*split, "sp"))
			process_sp(++split, scene);
		else if (!ft_strcmp(*split, "sq"))
			process_sq(++split, scene);
		else if (!ft_strcmp(*split, "cy"))
			process_cy(++split, scene);
		else if (!ft_strcmp(*split, "tr"))
			process_tr(++split, scene);
		else
			error("Incorrect RT specification. Please refer to the bible.", scene);
	}
}

void parse_rt(char *rt, t_scene *scene)
{
	int 	fd;
	int 	n;
	char 	*line;

	ft_bzero(scene, sizeof(t_scene));
	if ((fd = open(rt, O_RDONLY)) < 0)
		error(NULL, scene);
	while ((n = get_next_line(fd, &line)) > 0)
		process_line(line, scene);
	process_line(line, scene);
	if (n < 0)
		error(NULL, scene);
	if (close(fd) < 0)
		error(NULL, scene);
}
