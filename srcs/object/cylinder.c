#include "minirt.h"

t_cylinder	*init_cylinder(void)
{
	t_cylinder	*cylinder;
	int			ct;

	if (!(cylinder = ft_malloc(1, sizeof(t_cylinder))))
	{
		printf("Error\nERROR_IN_INIT_CYLINDER\n");
		return (NULL);
	}
	ct = -1;
	while (++ct < 3)
		cylinder->coordinate[ct] = 0.0;
	ct = -1;
	while (++ct < 3)
		cylinder->orientation[ct] = 0.0;
	ct = -1;
	while (++ct < 3)
		cylinder->color[ct] = 0;
	cylinder->diameter = 0.0;
	cylinder->height = 0.0;
	return (cylinder);
}

static void		cylinder_coef(double *coef, double *alpha, t_line *l, t_cylinder *cylinder)
{
	double	p[2][3];
	double	v[2][3];

	p[0][0] = cylinder->end_point[0][0];
	p[0][1] = cylinder->end_point[0][1];
	p[0][2] = cylinder->end_point[0][2];
	p[1][0] = l->x[1];
	p[1][1] = l->y[1];
	p[1][2] = l->z[1];
	v[0][0] = cylinder->orientation[0];
	v[0][1] = cylinder->orientation[1];
	v[0][2] = cylinder->orientation[2];
	v[1][0] = l->x[0];
	v[1][1] = l->y[0];
	v[1][2] = l->z[0];
	alpha[0] = v[0][0] * v[0][0] + v[0][1] * v[0][1] + v[0][2] * v[0][2];
	alpha[1] = v[1][0] * v[1][0] + v[1][1] * v[1][1] + v[1][2] * v[1][2];
	alpha[2] = dot((double*)v[0], (double*)v[1]);
	alpha[3] = dot((double*)v[0], (double*)p[0]);
	alpha[4] = dot((double*)v[0], (double*)p[1]);
	alpha[5] = dot((double*)v[1], (double*)p[0]);
	alpha[6] = dot((double*)v[1], (double*)p[1]);
	alpha[7] = p[0][0] * p[0][0] + p[0][1] * p[0][1] + p[0][2] * p[0][2];
	alpha[8] = p[1][0] * p[1][0] + p[1][1] * p[1][1] + p[1][2] * p[1][2];
	alpha[9] = dot((double*)p[0], (double*)p[1]);
	coef[0] = -1.0 * alpha[2] * alpha[2] / alpha[0] + alpha[1];
	coef[1] = 2.0 * alpha[2] * (alpha[3] - alpha[4]) / alpha[0] + 2.0 * (alpha[6] - alpha[5]);
	coef[2] = -1.0 * (alpha[4] - alpha[3]) * (alpha[4] - alpha[3]) / alpha[0] + alpha[7] + alpha[8] - 2 * alpha[9] - cylinder->diameter * cylinder->diameter / 4.0;
}

void			intersect_cy(t_intersect *is, t_line *l, void *ptr, int num)
{
	t_cylinder	*cylinder;
	double		coef[3];
	double		answer[2];
	double		alpha[10];
	double		s;
	int			ct;

	cylinder = (t_cylinder*)ptr;
	cylinder_coef(coef, alpha, l, cylinder);
	if (quadratic_equation(coef, answer) <= 0)
		return ;
	ct = -1;
	while (++ct < 2)
	{
		if (answer[ct] < 0.0)
			continue ;
		s = (alpha[2] * answer[ct] + alpha[4] - alpha[3]) / alpha[0];
		if (s <= 1e-6 || s >= 1.0 - 1e-6)
			continue ;
		if (is->intersect == 0 || answer[ct] < is->dist - 1e-6)
		{
			is->dist = answer[ct];
			is->intersect = 1;
			is->coordinate[0] = l->x[0] * is->dist + l->x[1];
			is->coordinate[1] = l->y[0] * is->dist + l->y[1];
			is->coordinate[2] = l->z[0] * is->dist + l->z[1];
			is->obj_num = num;
		}
	}
}

int				have_intersection_cy(t_line *l, void *ptr)
{
	t_cylinder	*cylinder;
	double		coef[3];
	double		answer[2];
	double		alpha[10];
	double		s;
	int			ct;

	cylinder = (t_cylinder*)ptr;
	cylinder_coef(coef, alpha, l, cylinder);
	if (quadratic_equation(coef, answer) <= 0)
		return (0);
	ct = -1;
	while (++ct < 2)
	{
		s = (alpha[2] * answer[ct] + alpha[4] - alpha[3]) / alpha[0];
		if (answer[ct] > 1e-6 && answer[ct] < 1.0 - 1e-6 && s > 1e-6 && s < 1.0 - 1e-6)
			return (1);
	}
	return (0);
}

double			*normal_vector_cy(double *point, void *ptr)
{
	t_cylinder	*cylinder;
	double		*ans;
	double		*vector[2];

	cylinder = ptr;
	if (dot(cylinder->coordinate, point) == dot(cylinder->coordinate, cylinder->end_point[0]) || dot(cylinder->coordinate, point) == dot(cylinder->coordinate, cylinder->end_point[1]))
	{
		if (!(ans = ft_malloc(3, sizeof(double))))
			error_exit("normal_vector_cy\n");
		ans[0] = cylinder->coordinate[0];
		ans[1] = cylinder->coordinate[1];
		ans[2] = cylinder->coordinate[2];
	}
	else
	{
		vector[0] = two_points_vector(cylinder->end_point[0], point);
		vector[1] = cross(vector[0], cylinder->coordinate);
		ans = cross(vector[1], cylinder->coordinate);
		ft_free(vector[0]);
		ft_free(vector[1]);
	}
	return (ans);
}
