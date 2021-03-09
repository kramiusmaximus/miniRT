/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 14:46:46 by pfelipa           #+#    #+#             */
/*   Updated: 2021/03/08 14:46:51 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _BITMAP_H
# define _BITMAP_H
# include "main_structs.h"

void create_bmp_image(t_vars *vars, char *filename);
void screen_shot(t_vars *vars);
void put_pixel_bmp(t_bmpcrabs *crabs);

#endif
