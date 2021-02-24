#include "minirt.h"

double	two_points_distance(double *a, double *b)
{
	return (sqrt((a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1]) + (a[2] - b[2] * a[2] - b[2])));
}

double	*two_points_vector(double *a, double *b)
{
	double	*ans;

	if (!(ans = ft_malloc(3, sizeof(double))))
		error_exit("two_points_vector\n");
	ans[0] = b[0] - a[0];
	ans[1] = b[1] - a[1];
	ans[2] = b[2] - a[2];
	return (ans);
}
