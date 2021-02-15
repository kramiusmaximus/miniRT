/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:42:45 by pfelipa           #+#    #+#             */
/*   Updated: 2020/09/02 18:56:32 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstremove(t_list **lst, int index)
{
	t_list *current;
	t_list *prev;

	if (!lst || !*lst)
		return ;
	current = *lst;
	if (!current->next || index == 0)
	{
		ft_lstdelone(current, (void (*)(void *)) ht_freeitem);
		*lst = NULL;
	}
	else
	{
		while (current)
		{
			if (index-- == 0)
				break ;
			prev = current;
			current = current->next;
		}
		prev->next = current->next;
		ft_lstdelone(current, (void (*)(void *)) ht_freeitem);
	}
}
