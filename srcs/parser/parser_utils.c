#include "miniRT.h"

int 		is_int(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int 		is_float(char *str)
{
	while (*str == '+' || *str == '-')
		str++;
	while (ft_isdigit(*str))
		str++;
	if (*str == '.')
		str++;
	while (ft_isdigit(*str))
		str++;
	if (*str)
		return (0);
	return (1);
}

int 		is_input_color(char *str)
{
	char 	**rgb;
	int 	k;
	int		i;

	i = 0;
	rgb = ft_split(str, ',');
	while (rgb[i])
	{
		if (i > 2 || !is_int(*rgb))
			return (0);
		k = ft_atoi(rgb[i++]);
		if (k < 0 || k > 255)
			return (0);
	}
	return (1);
}

int 		is_coords(char *str)
{
	char **coord;
	int i;

	i = 0;
	coord = ft_split(str, ',');
	while (coord[i])
	{
		if (i > 2 || !is_float(coord[i++]))
			return (0);
	}
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