#include "minirt.h"

double	two_points_distance(double *a, double *b)
{
	return (sqrt((a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1]) + (a[2] - b[2] * a[2] - b[2])));
}