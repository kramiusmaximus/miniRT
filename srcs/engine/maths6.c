/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:53:32 by pfelipa           #+#    #+#             */
/*   Updated: 2021/03/08 17:53:35 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_v	get_component(t_m mat, int col)
{
	t_v v;
	int i;

	i = 0;
	while (i < mat.size[0])
	{
		v.v[i] = mat.m[i][col];
		i++;
	}
	return (v);
}

t_v	v_mid(t_v v1, t_v v2)
{
	t_v mid;
	t_v dir;

	dir = v_sub(v2, v1);
	mid = v_add(v1, v_smult(dir, 0.5));
	return (mid);
}
