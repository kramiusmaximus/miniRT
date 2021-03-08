#include "minirt.h"

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
	int		i;
	int 	k;

	k = 1;
	if (!*arg)
		return (0);
	i = 0;
	rgb = ft_split(*arg, ',');
	while (rgb[i])
	{
		if (!is_int(&rgb[i]))
		{
			k = 0;
			break;
		}
		i++;
	}
	if (i != 3)
		k = 0;
	free_split(rgb);
	return (k);
}

int 		is_coord(char **arg)
{
	char 	**coord;
	int 	i;
	int 	k;

	k = 1;
	if (!*arg)
		return (0);
	i = 0;
	coord = ft_split(*arg, ',');
	while (coord[i])
	{
		if (!is_float(&coord[i]))
		{
			k = 0;
			break;
		}
		i++;
	}
	if (i != 3)
		k = 0;
	free_split(coord);
	return (k);
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
