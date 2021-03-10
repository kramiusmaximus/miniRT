/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:30:48 by pfelipa           #+#    #+#             */
/*   Updated: 2021/03/09 11:30:50 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			get_pixel_color(int v, int h, t_vars *vars)
{
	t_v		ve[2];
	t_ray	ray;
	int		c[AA_SAMPLE_NUM];
	int		i[2];
	double	d[2];

	d[0] = 1;
	d[1] = MAX_DIST;
	i[1] = !vars->full_res_rendered ? 1 : AA_SAMPLE_NUM;
	i[0] = 0;
	while (i[0] < i[1])
	{
		ve[0] = screen_to_world(h, v, vars, i[1] > 1 ? 1 : 0);
		ve[1] = v_sub(ve[0], ((t_cam *)vars->scene.camera->cntnt)->coord);
		ray = make_ray(((t_cam *)vars->scene.camera->cntnt)->coord,\
		ve[1], 0);
		c[i[0]++] = trace_color(&ray, &vars->scene, N_PASSES, d);
	}
	return (rgb_avg(c, i[1]));
}

static int	render_image(t_vars *vars)
{
	t_render	rvars;
	int			h;
	int			v;

	rvars.vars = vars;
	rvars.mult[0] = 1 / vars->af;
	rvars.mult[1] = 1 / vars->af;
	v = 0;
	while (v < (int)(((double)vars->scene.res.ht) * vars->af))
	{
		h = 0;
		while (h < (int)(((double)vars->scene.res.width) * vars->af))
		{
			rvars.color = get_pixel_color(v, h, vars);
			fill_square(&rvars, v, h);
			h++;
		}
		v++;
	}
	return (0);
}

int			render_mlx(t_vars *vars)
{
	if (is_moving(&vars->nav) || is_rotating(&vars->nav))
	{
		move_camera(vars);
		vars->full_res_rendered = 0;
		vars->af = AF;
	}
	else if (!vars->full_res_rendered)
	{
		vars->full_res_rendered = 1;
		vars->af = 1;
	}
	else
		return (0);
	if (THRDS > 1)
		render_multi(vars);
	else
		render_image(vars);
	mlx_put_image_to_window(vars->mlx.mlx,\
	vars->mlx.win, vars->mlx.image.img, 0, 0);
	return (0);
}
