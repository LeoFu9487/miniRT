#include "minirt.h"

t_cone			*init_cone(void)
{
	t_cone		*cone;
	int			ct;

	if (!(cone = ft_malloc(1, sizeof(t_cone))))
	{
		printf("Error\nERROR_IN_INIT_CYLINDER\n");
		return (NULL);
	}
	ct = -1;
	while (++ct < 3)
		cone->coordinate[ct] = 0.0;
	ct = -1;
	while (++ct < 3)
		cone->orientation[ct] = 0.0;
	ct = -1;
	while (++ct < 3)
		cone->color[ct] = 0;
	cone->diameter = 0.0;
	cone->height = 0.0;
	return (cone);
}

static void		cone_coef(double *coef, double *alpha, t_line *l, t_cone *cone)
{
	double	p[2][3];
	double	v[2][3];

	p[0][0] = cone->end_point[0][0];
	p[0][1] = cone->end_point[0][1];
	p[0][2] = cone->end_point[0][2];
	p[1][0] = l->x[1];
	p[1][1] = l->y[1];
	p[1][2] = l->z[1];
	v[0][0] = cone->orientation[0];
	v[0][1] = cone->orientation[1];
	v[0][2] = cone->orientation[2];
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
	coef[0] = -1.0 * alpha[2] * alpha[2] / alpha[0] + alpha[1] - cone->diameter * cone->diameter * alpha[2] * alpha[2] / (4.0 * alpha[0] * alpha[0]);
	coef[1] = 2.0 * alpha[2] * (alpha[3] - alpha[4]) / alpha[0] + 2.0 * (alpha[6] - alpha[5]) + cone->diameter * cone->diameter * alpha[2] * (alpha[0] + alpha[3] - alpha[4]) / (2.0 * alpha[0] * alpha[0]);
	coef[2] = -1.0 * (alpha[4] - alpha[3]) * (alpha[4] - alpha[3]) / alpha[0] + alpha[7] + alpha[8] - 2 * alpha[9] - cone->diameter * cone->diameter * (alpha[4] - alpha[3]) * (alpha[4] - alpha[3]) / (4.0 * alpha[0] * alpha[0]) +
	cone->diameter * cone->diameter * (alpha[4] - alpha[3]) / (2.0 * alpha[0]) - cone->diameter * cone->diameter / 4.0;
}

void			intersect_co(t_intersect *is, t_line *l, void *ptr, int num)
{
	t_cone		*cone;
	double		coef[3];
	double		answer[2];
	double		alpha[10];
	double		v[3][3];
	double		s;
	int			ct;

	cone = (t_cone*)ptr;
	ct = -1;
	v[0][0] = l->x[1];
	v[0][1] = l->y[1];
	v[0][2] = l->z[1];
	v[1][0] = l->x[0];
	v[1][1] = l->y[0];
	v[1][2] = l->z[0];
	while (++ct < 1)
	{
		s = (dot(cone->orientation, cone->end_point[ct]) - dot(cone->orientation, (double*)v[0])) / dot(cone->orientation, (double*)v[1]);
		if (s <= 0.0)
			continue ;
		v[2][0] = v[0][0] + v[1][0] * s;
		v[2][1] = v[0][1] + v[1][1] * s;
		v[2][2] = v[0][2] + v[1][2] * s;
		if (two_points_distance((double*)v[2], (double*)cone->end_point[ct]) <= cone->diameter / 2.0)
		{
			if (is->intersect == 0 || s < is->dist - 1e-6)
			{
				is->dist = s;
				is->intersect = 1;
				is->coordinate[0] = l->x[0] * is->dist + l->x[1];
				is->coordinate[1] = l->y[0] * is->dist + l->y[1];
				is->coordinate[2] = l->z[0] * is->dist + l->z[1];
				is->obj_num = num;
			}
		}
	}
	cone_coef(coef, alpha, l, cone);
	if (quadratic_equation(coef, answer) <= 0)
		return ;
	ct = -1;
	while (++ct < 2)
	{
		if (answer[ct] <= 0.0)
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

int				have_intersection_co(t_line *l, void *ptr)
{
	t_cone		*cone;
	double		coef[3];
	double		answer[2];
	double		alpha[10];
	double		s;
	double		v[3][3];
	int			ct;

	cone = (t_cone*)ptr;
	ct = -1;
	v[0][0] = l->x[1];
	v[0][1] = l->y[1];
	v[0][2] = l->z[1];
	v[1][0] = l->x[0];
	v[1][1] = l->y[0];
	v[1][2] = l->z[0];
	while (++ct < 1)
	{
		s = (dot(cone->orientation, cone->end_point[ct]) - dot(cone->orientation, (double*)v[0])) / dot(cone->orientation, (double*)v[1]);
		if (s <= 1e-6 || s >= 1.0 - 1e-6)
			continue ;
		v[2][0] = v[0][0] + v[1][0] * s;
		v[2][1] = v[0][1] + v[1][1] * s;
		v[2][2] = v[0][2] + v[1][2] * s;
		if (two_points_distance((double*)v[2], (double*)(cone->end_point[ct])) <= cone->diameter / 2.0)
			return (1);
	}
	cone_coef(coef, alpha, l, cone);
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

double			*normal_vector_co(double *point, void *ptr)
{
	t_cone		*cone;
	double		*ans;
	double		*vector[3];

	cone = ptr;
	if (double_abs(dot(cone->orientation, point) - dot(cone->orientation, cone->end_point[0])) < 1e-6)
	{
		if (!(ans = ft_malloc(3, sizeof(double))))
			error_exit("normal_vector_cy\n");
		ans[0] = cone->orientation[0];
		ans[1] = cone->orientation[1];
		ans[2] = cone->orientation[2];
	}
	else
	{
		vector[0] = two_points_vector(cone->end_point[1], point);
		vector[1] = two_points_vector(cone->end_point[1], cone->end_point[0]);
		vector[2] = cross(vector[0], vector[1]);
		ans = cross(vector[0], vector[2]);
		ft_free(vector[0]);
		ft_free(vector[1]);
		ft_free(vector[2]);
	}
	return (ans);
}

