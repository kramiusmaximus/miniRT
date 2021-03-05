#ifndef _BITMAP_H
#define _BITMAP_H
# include "main_structs.h"

void create_bmp_image(t_vars *vars, char *filename);
void screen_shot(t_vars *vars);
void put_pixel_bmp(void *img, int x, int y, int color, int line_len, int bpp);

#endif
