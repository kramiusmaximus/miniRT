#include "miniRT.h"

int 	is_int(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int 	is_float(char *str)
{
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

int 	is_input_color(char *str)
{
	char 	**rgb;
	int 	i;
	int		j;

	j = 0;
	rgb = ft_split(str, ',');
	while (rgb[j])
	{
		if (j > 2)
			return (0);
		i = ft_atoi(*rgb++);
		if (i < 0 || i > 255)
			return (0);
	}
	return (1);
}

