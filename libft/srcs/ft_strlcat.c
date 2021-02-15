/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:42:45 by pfelipa           #+#    #+#             */
/*   Updated: 2020/09/02 18:56:32 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	reslen;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	reslen = (dstsize < dstlen) ? dstsize + srclen : dstlen + srclen;
	if (dstsize > dstlen)
	{
		dst += dstlen;
		ft_strlcpy(dst, src, dstsize - dstlen);
	}
	return (reslen);
}
