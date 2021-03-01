#include "miniRT.h"

void		ft_lstcadd_front(t_listc **head, t_listc *node)
{
	t_listc	*p;

	if (!head || !node)
		return ;
	if (!*head)
		*head = node;
	else
	{
		((*head)->prev)->next = node;
		node->prev = (*head)->prev;
		node->next = *head;
		(*head)->prev = node;
		*head = node;
	}
}

int 	extract_color(char *arg)
{
	int c;
	char **rgb;

	rgb = ft_split(arg, ',');
	c = rgb_create(0, ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	free(rgb);
	return (c);
}

t_v 	extract_coord(char *arg)
{
	t_v		v;
	char 	**coords;

	coords = ft_split(arg, ',');
	v.v[0] = ft_atof(coords[0]);
	v.v[1] = ft_atof(coords[1]);
	v.v[2] = ft_atof(coords[2]);
	free(coords);
	return (v);
}

t_v 	extract_dir(char *arg)
{
	t_v		v;
	char 	**dir;

	dir = ft_split(arg, ',');
	v = v_create(ft_atof(dir[0]), ft_atof(dir[1]), ft_atof(dir[2]));
	free(dir);
	v = v_normalize(v);
	return (v);
}
