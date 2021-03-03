/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 13:39:28 by yfu               #+#    #+#             */
/*   Updated: 2021/03/03 19:07:34 by yfu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void		assign_v(double v[3][3], t_line *l)
{
	v[0][0] = l->x[1];
	v[0][1] = l->y[1];
	v[0][2] = l->z[1];
	v[1][0] = l->x[0];
	v[1][1] = l->y[0];
	v[1][2] = l->z[0];
}

static void		intersect_co_sub(t_cone *cone,
t_intersect *is, t_line *l, int num)
{
	double	s;
	double	v[3][3];

	assign_v(v, l);
	s = (dot(cone->orientation, cone->end_point[0]) -
dot(cone->orientation, (double*)v[0])) / dot(cone->orientation, (double*)v[1]);
	if (s <= 0.0)
		return ;
	v[2][0] = v[0][0] + v[1][0] * s;
	v[2][1] = v[0][1] + v[1][1] * s;
	v[2][2] = v[0][2] + v[1][2] * s;
	if (two_points_distance((double*)v[2], (double*)cone->end_point[0])
	<= cone->diameter / 2.0)
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

void			intersect_co(t_intersect *is, t_line *l, void *ptr, int num)
{
	double	coef[3];
	double	answer[2];
	double	a[10];
	int		ct;

	intersect_co_sub(ptr, is, l, num);
	cone_coef(coef, a, l, ptr);
	if (quadratic_equation(coef, answer) <= 0)
		return ;
	ct = -1;
	while (++ct < 2)
	{
		if (answer[ct] <= 0.0 || (a[2] * answer[ct] + a[4] - a[3]) /
		a[0] <= 1e-6 || (a[2] * answer[ct] + a[4] - a[3]) / a[0] >= 1.0 - 1e-6)
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

static int		have_intersection_co_sub(t_cone *cone, double v[3][3], int ct)
{
	double	s;

	s = (dot(cone->orientation, cone->end_point[ct]) -
dot(cone->orientation, (double*)v[0])) / dot(cone->orientation, (double*)v[1]);
	if (s <= 1e-6 || s >= 1.0 - 1e-6)
		return (0);
	v[2][0] = v[0][0] + v[1][0] * s;
	v[2][1] = v[0][1] + v[1][1] * s;
	v[2][2] = v[0][2] + v[1][2] * s;
	if (two_points_distance((double*)v[2], (double*)(cone->end_point[ct]))
	<= cone->diameter / 2.0)
		return (1);
	return (0);
}

int				have_intersection_co(t_line *l, void *ptr)
{
	double		coef[3];
	double		answer[2];
	double		alpha[10];
	double		v[3][3];

	v[0][0] = l->x[1];
	v[0][1] = l->y[1];
	v[0][2] = l->z[1];
	v[1][0] = l->x[0];
	v[1][1] = l->y[0];
	v[1][2] = l->z[0];
	if (have_intersection_co_sub(ptr, v, 0))
		return (1);
	cone_coef(coef, alpha, l, ptr);
	if (quadratic_equation(coef, answer) <= 0)
		return (0);
	if ((answer[0] > 1e-6 && answer[0] < 1.0 - 1e-6 && (alpha[2] * answer[0] +
	alpha[4] - alpha[3]) / alpha[0] > 1e-6 && (alpha[2] * answer[0] + alpha[4]
	- alpha[3]) / alpha[0] < 1.0 - 1e-6) || (answer[1] > 1e-6 && answer[1] <
	1.0 - 1e-6 && (alpha[2] * answer[1] + alpha[4] - alpha[3]) / alpha[0] > 1e-6
	&& (alpha[2] * answer[1] + alpha[4] - alpha[3]) / alpha[0] < 1.0 - 1e-6))
		return (1);
	return (0);
}
