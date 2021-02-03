#include "miniRT.h"

int		get_t(int trgb)
{
	return (trgb & (0xFF << 24));
}

int		get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

int		get_g(int trgb)
{
	return (trgb & (0xFF << 8));
}

int		get_b(int trgb)
{
	return (trgb & 0xFF);
}

int rgb_create(int t, int r, int g, int b)
{
	int res;

	t = t < 0 ? 0 : t;
	t = t > 255 ? 255 : t;
	r = r < 0 ? 0 : r;
	r = r > 255 ? 255 : r;
	g = g < 0 ? 0 : g;
	g = g > 255 ? 255 : g;
	b = b < 0 ? 0 : b;
	b = b > 255 ? 255 : b;
	res = (t << 24 | r << 16 | g << 8 | b);
	return (res);
}

int rgb_multiply(int c1, int c2)
{
	return (rgb_create(get_t(c1) * get_t(c2), get_r(c1) * get_r(c2), get_g(c1) * get_g(c2), get_b(c1) * get_b(c2)));
}

int rgb_multiply_scalar(int c1, double s)
{
	return (rgb_create(get_t(c1), get_r(c1) * s, get_g(c1) * s, get_b(c1) * s));
}

int rgb_add(int c1, int c2)
{
	return (rgb_create(get_t(c1) + get_t(c2), get_r(c1) + get_r(c2), get_g(c1) + get_g(c2), get_b(c1) + get_b(c2)));
}