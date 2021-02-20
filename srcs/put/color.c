#include "minirt.h"

int		get_color(int *rgb)
{
	return (rgb[0] * 256 * 256 + rgb[1] * 256 + rgb[2]);
}

