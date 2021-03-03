/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 02:24:34 by yfu               #+#    #+#             */
/*   Updated: 2021/03/03 02:25:07 by yfu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	triangle_coef(double *coef, t_triangle *triangle)
{
	coef[0] = triangle->orientation[0];
	coef[1] = triangle->orientation[1];
	coef[2] = triangle->orientation[2];
	coef[3] = -1.0 * (triangle->point[0][0] * coef[0] +
	triangle->point[0][1] * coef[1] + triangle->point[0][2] * coef[2]);
}

static int	in_triangle(t_line *line, t_triangle *triangle, double t)
{
	double	point[3];
	double	*v;
	double	ans[2];

	point[0] = line->x[0] * t + line->x[1];
	point[1] = line->y[0] * t + line->y[1];
	point[2] = line->z[0] * t + line->z[1];
	v = two_points_vector(triangle->point[0], point);
	linear_equations(triangle->vector[0], triangle->vector[1], v, ans);
	ft_free(v);
	if (ans[0] > 1e-6 && ans[1] > 1e-6 && ans[0] + ans[1] <= 1.0 - 1e-6)
		return (1);
	return (0);
}

void		intersect_tr(t_intersect *is, t_line *l, void *ptr, int num)
{
	t_triangle	*triangle;
	double		coef[4];
	double		res;
	double		vector[3];

	triangle = ptr;
	vector[0] = l->x[0];
	vector[1] = l->y[0];
	vector[2] = l->z[0];
	res = cos_vector(triangle->orientation, vector);
	if (res < 1e-6 && res > -1e-6)
		return ;
	triangle_coef(coef, triangle);
	res = linear_equation(coef, l);
	if (res <= 0.0 || !(in_triangle(l, triangle, res)))
		return ;
	if (is->intersect == 0 || res < is->dist - 1e-6)
	{
		is->dist = res;
		is->intersect = 1;
		is->coordinate[0] = l->x[0] * is->dist + l->x[1];
		is->coordinate[1] = l->y[0] * is->dist + l->y[1];
		is->coordinate[2] = l->z[0] * is->dist + l->z[1];
		is->obj_num = num;
	}
}

int			have_intersection_tr(t_line *l, void *ptr)
{
	t_triangle	*triangle;
	double		coef[4];
	double		res;
	double		vector[3];

	triangle = ptr;
	vector[0] = l->x[0];
	vector[1] = l->y[0];
	vector[2] = l->z[0];
	res = cos_vector(triangle->orientation, vector);
	if (res < 1e-6 && res > -1e-6)
		return (0);
	triangle_coef(coef, triangle);
	res = linear_equation(coef, l);
	if (res > 1.0 - 1e-6 || res < 1e-6 || !(in_triangle(l, triangle, res)))
		return (0);
	return (1);
}

double		*normal_vector_tr(double *point, void *ptr)
{
	double		*ans;
	t_triangle	*triangle;

	(void)point;
	if (!(ans = ft_malloc(3, sizeof(double))))
		error_exit("normal_vector_tr\n");
	triangle = ptr;
	ans[0] = triangle->orientation[0];
	ans[1] = triangle->orientation[1];
	ans[2] = triangle->orientation[2];
	return (ans);
}
