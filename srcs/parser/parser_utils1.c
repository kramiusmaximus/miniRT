#include "miniRT.h"

int 		is_int(char **arg)
{
	char *p;

	if (!*arg)
		return (0);
	p = *arg;
	while (*p)
	{
		if (!ft_isdigit(*p))
			return (0);
		p++;
	}
	return (1);
}

int 		is_float(char **arg)
{
	char *p;

	if (!*arg)
		return (0);
	p = *arg;
	while (*p == '+' || *p == '-')
		p++;
	while (ft_isdigit(*p))
		p++;
	if (*p == '.')
		p++;
	while (ft_isdigit(*p))
		p++;
	if (*p)
		return (0);
	return (1);
}

int 		is_color(char **arg)
{
	char 	**rgb;
	int 	k;
	int		i;

	if (!*arg)
		return (0);
	i = 0;
	rgb = ft_split(*arg, ',');
	while (rgb[i])
	{
		if (!is_int(&rgb[i]))
			return (0);
		i++;
	}
	if (i != 3)
		return (0);
	return (1);
}

int 		is_coord(char **arg)
{
	char **coord;
	int i;

	if (!*arg)
		return (0);
	i = 0;
	coord = ft_split(*arg, ',');
	while (coord[i])
	{
		if (!is_float(&coord[i]))
			return (0);
		i++;
	}
	if (i != 3)
		return (0);
	return (1);
}

t_listc		*ft_lstcnew(t_camera *data)
{
	t_listc	*node;

	if (!(node = malloc(sizeof(t_listc))))
		return (NULL);
	node->content = data;
	node->next = node;
	node->prev = node;
	return (node);
}