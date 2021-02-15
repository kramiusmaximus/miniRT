/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:42:45 by pfelipa           #+#    #+#             */
/*   Updated: 2020/09/02 18:56:32 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ht_paircmpr(t_pair *a, char *key)
{
	if (!a || !key)
	{
		ft_putstr_fd("ht_paircmpr(...) error\n", 2);
		return (-69);
	}
	return (ft_strcmp(a->key, key));
}

void			ht_freeitem(t_pair *item)
{
	if (!item)
		return ;
	free(item->key);
	free(item->value);
	free(item);
}

t_pair			*ht_newpair(char *key, char *value)
{
	t_pair		*pair;

	if (!key || !value)
		return (NULL);
	pair = malloc(sizeof(t_pair));
	if (pair)
	{
		pair->key = ft_strdup(key);
		pair->value = ft_strdup(value);
	}
	return (pair);
}

void			ht_process_collision(t_ht *table, long index, t_pair *pair)
{
	int		found;
	t_list	*ptr;

	if (!table || !pair)
		return ;
	if ((found = ft_lstsearch(table->items[index],
		pair->key, (int (*)(void *, void *)) ht_paircmpr)) > -1)
	{
		ptr = ft_lstget(table->items[index], found);
		ht_freeitem(ptr->content);
		ptr->content = pair;
	}
	else
	{
		ft_lstadd_front(&(table->items[index]), ft_lstnew(pair));
		table->count++;
	}
}

t_ht			*ht_create(int size)
{
	t_ht	*table;

	table = malloc(sizeof(t_ht));
	table->count = 0;
	table->size = size;
	table->items = ft_calloc(size, sizeof(t_list **));
	return (table);
}
