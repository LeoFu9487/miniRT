#include "minirt.h"

double	det(double **mat, int size)
{
	double	ans;
	double	**submat;
	int		ct[1];

	if (size == 1)
		return (mat[0][0]);
	ans = 0.0;
	ct[0] = -1;
	submat = ft_malloc((size - 1), sizeof(double*));
	while (++ct[0] < size - 1)
		submat[ct[0]] = &(mat[ct[0] + 1][1]);
	ct[0] = -1;
	while (++ct[0] < size)
	{
		if (ct[0] % 2)
			ans -= mat[ct[0]][0] * det(submat, size - 1);
		else
			ans += mat[ct[0]][0] * det(submat, size - 1);
		submat[ct[0]] = &(mat[ct[0]][1]);
	}
	ft_free(submat);
	return (ans);
}

double	point_to_line_distance(double *point, t_line *line)
{
	double	*v[5];
	double	ans;

	v[1] = make_point(line->x[1], line->y[1], line->z[1]);
	v[0] = make_point(line->x[0], line->y[0], line->z[0]);
	v[2] = two_points_vector(point, v[1]);
	v[3] = cross(v[0], v[2]);
	v[4] = cross(v[3], v[0]);
	ans = 0.0;
	/*
		k * v[4] + point is on the line
	*/
	if (v[4][0] != 0.0)
	{
		
	}
	else if (v[4][1] != 0.0)
	{

	}
	else if (v[4][2] != 0.0)
	{

	}
	return (ans);
}
