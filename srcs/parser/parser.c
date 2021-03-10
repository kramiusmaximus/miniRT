/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 15:04:04 by pfelipa           #+#    #+#             */
/*   Updated: 2021/03/10 15:04:09 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	anal_beads(char **split, t_scene *scene)
{
	if (!ft_strcmp(*split, "cy"))
		process_cy(split + 1, scene);
	else if (!ft_strcmp(*split, "tr"))
		process_tr(split + 1, scene);
	else
		error("Incorrect RT specification. Please refer to the bible.", scene);
}

static void	process_line(char *line, t_scene *scene)
{
	char **split;

	if ((split = ft_split(line, ' ')) && *split)
	{
		if (!ft_strcmp(*split, "R") && !(scene->s & 0b00000001))
			process_r(split + 1, scene);
		else if (!ft_strcmp(*split, "A") && !(scene->s & 0b00000010))
			process_a(split + 1, scene);
		else if (!ft_strcmp(*split, "c"))
			process_c(split + 1, scene);
		else if (!ft_strcmp(*split, "l"))
			process_l(split + 1, scene);
		else if (!ft_strcmp(*split, "pl"))
			process_pl(split + 1, scene);
		else if (!ft_strcmp(*split, "sp"))
			process_sp(split + 1, scene);
		else if (!ft_strcmp(*split, "sq"))
			process_sq(split + 1, scene);
		else
			anal_beads(split, scene);
	}
	free_split(split);
	free(line);
}

void		parse_rt(char *rt, t_scene *scene)
{
	int		fd;
	int		n;
	char	*line;

	ft_bzero(scene, sizeof(t_scene));
	if ((fd = open(rt, O_RDONLY)) < 0)
		error(NULL, scene);
	while ((n = get_next_line(fd, &line)) > 0)
		process_line(line, scene);
	process_line(line, scene);
	if (!((scene->s & 0b00000001) && (scene->s & 0b00000010) && scene->camera))
		error("Missing necessary objects in *.rt file.", scene);
	if (n < 0 || close(fd) < 0)
		error(NULL, scene);
}
