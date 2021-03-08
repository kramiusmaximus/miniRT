#include "minirt.h"

void free_split(char **split)
{
	char **p;

	if (!split)
		return ;
	p = split;
	while (*p)
		free(*p++);
	free(split);
}
