/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:42:45 by pfelipa           #+#    #+#             */
/*   Updated: 2020/09/02 18:56:32 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_charin(char const c, char const *set)
{
	while (*set)
	{
		if (*set++ == c)
			return (1);
	}
	return (0);
}

char		*ft_strtrim(char const *s, char const *set)
{
	int		start;
	int		end;

	if (!s || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s);
	while (ft_charin(s[start], set))
		start++;
	while (ft_charin(s[end - 1], set))
		end--;
	if (start < end)
		return (ft_substr(s, start, end - start));
	return (ft_calloc(1, sizeof(char)));
}
