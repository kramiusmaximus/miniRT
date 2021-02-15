/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:42:45 by pfelipa           #+#    #+#             */
/*   Updated: 2020/09/02 18:56:32 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		*ft_execute_order_66(char **buff, int len)
{
	int i;

	i = 0;
	while (i < len)
		free(buff[i++]);
	free(buff);
	return (NULL);
}

static int		ft_len_counter(char const *s, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
		if (s[i])
			i++;
	}
	return (count + 1);
}

char			**ft_split(char const *s, char c)
{
	char	**res;
	int		start;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s || !(res = malloc(ft_len_counter(s, c) * sizeof(char *))))
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			if (!(res[j++] = ft_substr(s, start, i - start)))
				return (ft_execute_order_66(res, j - 1));
		}
		else
			i++;
	}
	res[j] = NULL;
	return (res);
}
