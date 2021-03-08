/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfelipa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 14:51:52 by pfelipa           #+#    #+#             */
/*   Updated: 2021/03/08 14:52:00 by pfelipa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_STRUCTS_H
# define MAIN_STRUCTS_H
# include "../libft/includes/libft.h"

typedef struct
{
	unsigned char		b;
	unsigned char		g;
	unsigned char		r;
}						t_bmp_pix;

# pragma pack(push)
# pragma pack(1)

typedef struct
{
	uint16_t			type;
	uint32_t			size;
	uint16_t			reserved1;
	uint16_t			reserved2;
	uint32_t			offset;
	uint32_t			dib_header_size;
	int32_t				width_px;
	int32_t				height_px;
	uint16_t			num_planes;
	uint16_t			bits_per_pixel;
	uint32_t			compression;
	uint32_t			image_size_bytes;
	int32_t				x_resolution_ppm;
	int32_t				y_resolution_ppm;
	uint32_t			num_colors;
	uint32_t			important_colors;
}	t_bmpheader;
# pragma pack(pop)

typedef struct
{
	t_bmpheader			header;
	int					pad_size;
	unsigned char		*image;
}	t_bmpimage;

typedef struct
{
	double				t;
	t_object			*obj;
	t_v					contact;
	double				incidence_ang0;
	double				incidence_ang1;
	t_v					ref_dir;
	t_v					tra_dir;
	double				ref_coeff;
	t_v					surface_v;
}						t_intersect;

typedef struct
{
	t_v					orgn;
	t_v					dir;
	int					inside;
	t_intersect			*intersect;
}	t_ray;

typedef struct
{
	t_v					l;
	t_list				*p;
	t_light				*light;
	t_intersect			*inter_l;
	t_ray				ray_l;
	double				dot;
	double				dist;
	double				pass;
	int					amb;
	int					diff;
	int					spec;
}	t_lvars;

typedef struct
{
	t_v					coord;
	t_v					dir;
	t_m					rot_mat;
	double				fov;
}	t_camera;

typedef struct			s_listc
{
	t_camera			*content;
	struct s_listc		*prev;
	struct s_listc		*next;
}						t_listc;

typedef struct			s_dims
{
	int					height;
	int					width;
}						t_dims;

typedef struct			s_scene
{
	int					s;
	t_dims				res;
	t_ambient			ambient;
	t_listc				*camera;
	t_list				*light;
	t_list				*object;
}						t_scene;

typedef struct			s_image
{
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}						t_image;

typedef struct			s_mlx
{
	void				*mlx;
	void				*win;
	t_dims				window_dims;
	t_image				image;
}						t_mlx;

typedef struct
{
	int					fwd_back;
	int					lft_rght;
	int					up_dwn;
	int					rot_lft_rght;
	int					rot_up_dwn;
}						t_nav;

typedef struct			s_toomuchass
{
	t_bmpimage			bmpim;
	t_mlx				mlx;
	t_scene				scene;
	int					full_res_rendered;
	double				af;
	t_nav				nav;
}						t_vars;

typedef struct			s_moreass
{
	t_vars				*vars;
	int					tid;
}						t_tvars;

typedef struct			s_ass
{
	t_vars				*vars;
	int					tid;
	t_scene				*scene;
	t_v					vec[2];
	double				mult[2];
	int					color;
	t_ray				ray;
}						t_render;

#endif
