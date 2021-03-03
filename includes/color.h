#ifndef VISUAL_H
#define VISUAL_H

int				get_t(int trgb);
int				get_r(int trgb);
int				get_g(int trgb);
int				get_b(int trgb);
int				rgb_create(int t, int r, int g, int b);
int				rgb_multiply(int c1, int c2);
int				rgb_multiply_scalar(int c1, double s);
int				rgb_add(int c1, int c2);
int 			rgb_add_weighted(int c1, int c2, double w);
int 			rgb_subtract(int c1, int c2);
int 			rgb_avg(int arr[], int n);

#endif
