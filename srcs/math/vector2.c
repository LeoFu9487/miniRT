#include "minirt.h"

double	two_points_distance(double *a, double *b)
{
	return (sqrt((a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1]) + (a[2] - b[2]) * (a[2] - b[2])));
}

double	*two_points_vector(double *start_point, double *end_point)
{
	double	*ans;

	if (!(ans = ft_malloc(3, sizeof(double))))
		error_exit("two_points_vector\n");
	ans[0] = end_point[0] - start_point[0];
	ans[1] = end_point[1] - start_point[1];
	ans[2] = end_point[2] - start_point[2];
	return (ans);
}

double	*make_point(double a, double b, double c)
{
	double	*ans;

	if (!(ans = ft_malloc(3, sizeof(double))))
		error_exit("make_point\n");
	ans[0] = a;
	ans[1] = b;
	ans[2] = c;
	return (ans);
}
