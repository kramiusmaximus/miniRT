/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsearch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:42:45 by pfelipa           #+#    #+#             */
/*   Updated: 2020/09/02 18:56:32 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstsearch(t_list *lst, void *content, int (*f)(void *, void *))
{
	int index;

	index = 0;
	if (!lst || !content || !f)
		return (-1);
	while (lst)
	{
		if (!f(lst->content, content))
			return (index);
		lst = lst->next;
		index++;
	}
	return (-1);
}
