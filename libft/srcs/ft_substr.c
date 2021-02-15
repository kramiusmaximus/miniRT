/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:42:45 by pfelipa           #+#    #+#             */
/*   Updated: 2020/09/02 18:56:32 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char *sub;
	char *ptr;

	if (!s)
		return (NULL);
	if ((size_t)start >= (size_t)ft_strlen(s))
		return (ft_calloc(1, sizeof(char)));
	sub = malloc(sizeof(char) * (len + 1));
	if (sub)
	{
		ptr = sub;
		while (*s && len-- > 0)
			*ptr++ = s[start++];
		*ptr = '\0';
	}
	return (sub);
}
