#ifndef MAIN_STRUCTS_H
# define MAIN_STRUCTS_H
# include "../libft/includes/libft.h"

typedef struct
{
	unsigned char 	b;
	unsigned char 	g;
	unsigned char 	r;
}					bmp_pix;

# pragma pack(push)  // save the original data alignment
# pragma pack(1)     // Set data alignment to 1 byte boundary
typedef struct	s_BMPHeader
{             				    // Total: 54 bytes
	uint16_t	type;             // Magic identifier: 0x4d42
	uint32_t  	size;             // File size in bytes
	uint16_t  	reserved1;        // Not used
	uint16_t  	reserved2;        // Not used
	uint32_t  	offset;           // Offset to image data in bytes from beginning of file (54 bytes)
	uint32_t  	dib_header_size;  // DIB Header size in bytes (40 bytes)
	int32_t   	width_px;         // Width of the image
	int32_t   	height_px;        // Height of image
	uint16_t  	num_planes;       // Number of color planes
	uint16_t  	bits_per_pixel;   // Bits per pixel
	uint32_t  	compression;      // Compression type
	uint32_t  	image_size_bytes; // Image size in bytes including pad_size
	int32_t   	x_resolution_ppm; // Pixels per meter
	int32_t   	y_resolution_ppm; // Pixels per meter
	uint32_t  	num_colors;       // Number of colors
	uint32_t  	important_colors; // Important colors
} 				t_BMPHeader;
# pragma pack(pop)

typedef struct
{
	t_BMPHeader 	header;
	int 			pad_size;
	unsigned char 	*image;
} 				t_BMPImage;

typedef struct			s_intersect
{
	double 				t;
	t_object			*obj;
	t_v 				contact;
	double 				incidence_ang0;
	double 				incidence_ang1;
	t_v					ref_dir;
	t_v					tra_dir;
	t_v					surface_v;
}						t_intersect;

typedef struct 			s_ray
{
	t_v 				origin;
	t_v					dir;
	int 				inside;
	t_intersect			*intersect;
}						t_ray;

typedef struct		s_camera
{
	t_v				coord;
	t_v 			dir;
	t_m				basis;
	double 			fov;
}					t_camera;

typedef struct			s_listc
{
	t_camera			*content;
	struct s_listc		*prev;
	struct s_listc		*next;
}						t_listc;

typedef struct 		s_dims
{
	int 			height;
	int				width;
}					t_dims;

typedef struct		s_scene
{
	int 			s;
	t_dims			res;
	t_ambient		ambient;
	t_listc			*camera;
	t_list			*light;
	t_list			*object;
}					t_scene;

typedef struct  	s_image
{
	void        	*img;
	char        	*addr;
	int         	bits_per_pixel;
	int         	line_length;
	int         	endian;
}               	t_image;

typedef struct  	s_mlx
{
	void        	*mlx;
	void        	*win;
	t_dims 			window_dims;
	t_image 		image;
}               	t_mlx;

typedef struct 		s_nav
{
	int 			fwd_back;
	int 			lft_rght;
	int 			up_dwn;
	int 			rot_lft_rght;
	int 			rot_up_dwn;
}					t_nav;

typedef struct 		s_vars
{
	t_BMPImage 		bmpim;
	t_mlx			mlx;
	t_scene			scene;
	int 			rendered;
	double 			af;
	t_nav			nav;
}					t_vars;

typedef struct 		s_tvars
{
	t_vars			*vars;
	int 			tid;
}					t_tvars;

typedef struct 		s_render
{
	t_vars			*vars;
	int 			tid;
	t_scene			*scene;
	t_v 			vec[2];
	double 			mult[2];
	int 			color;
	t_ray			ray;
}					t_render;



#endif
