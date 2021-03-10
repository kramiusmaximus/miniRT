/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 14:47:03 by pfelipa           #+#    #+#             */
/*   Updated: 2021/03/08 14:49:51 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

int				get_t(int trgb);
int				get_r(int trgb);
int				get_g(int trgb);
int				get_b(int trgb);
int				rgb_create(int t, int r, int g, int b);
int				rgb_multiply(int c1, int c2);
int				rgb_smult(int c1, double s);
int				rgb_add(int c1, int c2);
int				rgb_add_weighted(int c1, int c2, double w);
int				rgb_subtract(int c1, int c2);
int				rgb_avg(int arr[], int n);

#endif
