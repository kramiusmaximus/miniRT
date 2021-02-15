/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:42:45 by pfelipa           #+#    #+#             */
/*   Updated: 2020/09/02 18:56:32 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const unsigned char	*ptrsrc;
	unsigned char		*ptrdst;
	const unsigned char	*lasts;
	unsigned char		*lastd;

	ptrdst = dst;
	ptrsrc = src;
	if (dst <= src)
		ft_memcpy(dst, src, len);
	else
	{
		lasts = ptrsrc + (len - 1);
		lastd = ptrdst + (len - 1);
		while (len-- > 0)
			*lastd-- = *lasts--;
	}
	return (dst);
}
