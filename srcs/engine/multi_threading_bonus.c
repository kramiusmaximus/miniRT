/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_threading_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:22:52 by pfelipa           #+#    #+#             */
/*   Updated: 2021/03/09 11:23:51 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void		*render_section(void *arg)
{
	t_render	rvars;
	int			sec_h;

	rvars.rem = 0;
	rvars.vars = ((t_tvars *)arg)->vars;
	rvars.tid = ((t_tvars *)arg)->tid;
	rvars.mult[0] = 1 / rvars.vars->af;
	rvars.mult[1] = 1 / rvars.vars->af;
	sec_h = (int)((double)rvars.vars->scene.res.ht * rvars.vars->af / THRDS);
	if (rvars.tid == THRDS - 1 && !rvars.vars->full_res_rendered)
		rvars.rem = (int)((double)rvars.vars->scene.res.ht\
		* rvars.vars->af) % sec_h;
	rvars.v = rvars.tid * sec_h;
	while (rvars.v < (rvars.tid + 1) * sec_h + rvars.rem)
	{
		rvars.h = 0;
		while (rvars.h < rvars.vars->scene.res.width * rvars.vars->af)
		{
			rvars.color = get_pixel_color(rvars.v, rvars.h, rvars.vars);
			fill_square(&rvars, rvars.v, rvars.h++);
		}
		rvars.v++;
	}
	pthread_exit(NULL);
}

int				render_multi(t_vars *vars)
{
	t_tvars		tvars[THRDS];
	pthread_t	threads[THRDS];
	int			tid;

	tid = 0;
	while (tid < THRDS)
	{
		tvars[tid].tid = tid;
		tvars[tid].vars = vars;
		pthread_create(&threads[tid], NULL,\
		render_section, (void *)&tvars[tid]);
		tid++;
	}
	tid = 0;
	while (tid < THRDS)
		pthread_join(threads[tid++], NULL);
	return (0);
}
