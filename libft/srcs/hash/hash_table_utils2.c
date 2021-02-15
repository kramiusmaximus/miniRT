/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:42:45 by pfelipa           #+#    #+#             */
/*   Updated: 2020/09/02 18:56:32 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ht_freetable(t_ht *table)
{
	int		i;
	t_list	*item;

	i = 0;
	if (!table)
		return ;
	while (i < table->size)
	{
		item = table->items[i];
		if (item)
			ft_lstclear(&item, (void (*)(void *)) ht_freeitem);
		i++;
	}
	free(table->items);
	free(table);
}

void				ht_insert(t_ht *table, char *key, char *value)
{
	t_pair		*pair;
	long		index;
	t_list		*ptr;

	if (!table || !(pair = ht_newpair(key, value)))
		return ;
	index = hash_s(key, table->size);
	if (!table->items[index])
	{
		ptr = ft_lstnew(pair);
		table->items[index] = ptr;
		table->count++;
	}
	else
		ht_process_collision(table, index, pair);
}

void				ht_remove(t_ht *table, char *key)
{
	long	index;
	int		found;
	t_list	*lst;

	if (!table)
		return ;
	index = hash_s(key, table->size);
	lst = table->items[index];
	if (lst)
	{
		if ((found = ft_lstsearch(lst, key,
			(int (*)(void *, void *)) ht_paircmpr)) > -1)
		{
			ft_lstremove(&table->items[index], found);
			table->count--;
			ft_putstr_fd("Item removed from hashtable.\n", 1);
			return ;
		}
	}
	ft_putstr_fd("Item not found in hashtable.\n", 1);
}

static void			ht_printitem(t_pair *pair)
{
	ft_putstr_fd(pair->key, 1);
	ft_putstr_fd(pair->value, 1);
	ft_putchar_fd('\n', 1);
}

void				ht_print(t_ht *hashtable)
{
	int		index;
	t_list	*current;

	index = 0;
	while (index < hashtable->size)
	{
		if ((current = hashtable->items[index]))
		{
			while (current)
			{
				ft_putstr_fd("Bucket %d: ", index);
				ht_printitem(current->content);
				current = current->next;
			}
		}
		index++;
	}
}
