#include "miniRT.h"

int rgb_multiply(int c1, int c2)
{
	int t = get_t(c1);
	int r = get_r(c1) * get_r(c2) / 255;
	int g = get_g(c1) * get_g(c2) / 255;
	int b= get_b(c1) * get_b(c2) / 255;

	return (rgb_create(t, r, g, b));
}

int rgb_multiply_scalar(int c1, double s)
{
	int t = get_t(c1);
	int r = (double)get_r(c1) * s;
	int g = (double)get_g(c1) * s;
	int b = (double)get_b(c1) * s;

	return (rgb_create(t, r, g, b));
}

int rgb_add(int c1, int c2)
{
	int t = get_t(c1);
	int r = get_r(c1) + get_r(c2);
	int g = get_g(c1) + get_g(c2);
	int b= get_b(c1) + get_b(c2);

	return (rgb_create(t, r, g, b));
}

int rgb_add_weighted(int c1, int c2, double w)
{
	int t = get_t(c1);
	int r = rgb_multiply_scalar(get_r(c1), w) + rgb_multiply_scalar(get_r(c2), 1 - w);
	int g = rgb_multiply_scalar(get_g(c1), w) + rgb_multiply_scalar(get_g(c2), 1 - w);
	int b = rgb_multiply_scalar(get_b(c1), w) + rgb_multiply_scalar(get_b(c2), 1 - w);

	return (rgb_create(t, r, g, b));
}

int rgb_avg(int arr[], int n)
{
	int rgb[3] = {0,0,0};
	int avg;
	int i;

	i = 0;
	while (i < n)
	{
		rgb[0] += get_r(arr[i]);
		rgb[1] += get_g(arr[i]);
		rgb[2] += get_b(arr[i]);
		i++;
	}
	avg = rgb_create(0, rgb[0] / n, rgb[1] / n, rgb[2] / n);
	return (avg);
}
