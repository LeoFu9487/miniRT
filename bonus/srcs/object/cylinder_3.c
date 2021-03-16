/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 21:22:20 by yfu               #+#    #+#             */
/*   Updated: 2021/03/03 21:33:42 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void		intersect_cy_sub_1(t_cylinder *cylinder,
t_intersect *is, t_line *l, int num)
{
	double	s;
	double	v[3][3];

	assign_v(v, l);
	s = (dot(cylinder->orientation, cylinder->end_point[0]) -
dot(cylinder->orientation, (double*)v[0])) / dot(cylinder->orientation,
(double*)v[1]);
	if (s <= 0.0)
		return ;
	v[2][0] = v[0][0] + v[1][0] * s;
	v[2][1] = v[0][1] + v[1][1] * s;
	v[2][2] = v[0][2] + v[1][2] * s;
	if (two_points_distance((double*)v[2], (double*)cylinder->end_point[0])
	<= cylinder->diameter / 2.0)
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

static void		intersect_cy_sub_2(t_cylinder *cylinder,
t_intersect *is, t_line *l, int num)
{
	double	s;
	double	v[3][3];

	assign_v(v, l);
	s = (dot(cylinder->orientation, cylinder->end_point[1]) -
dot(cylinder->orientation, (double*)v[0])) / dot(cylinder->orientation,
(double*)v[1]);
	if (s <= 0.0)
		return ;
	v[2][0] = v[0][0] + v[1][0] * s;
	v[2][1] = v[0][1] + v[1][1] * s;
	v[2][2] = v[0][2] + v[1][2] * s;
	if (two_points_distance((double*)v[2], (double*)cylinder->end_point[1])
	<= cylinder->diameter / 2.0)
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

static void		intersect_cy_sub__1(double alpha[10],
t_intersect *is, t_line *l, int num)
{
	double	s;

	if (alpha[10] <= 0.0)
		return ;
	s = (alpha[2] * alpha[10] + alpha[4] - alpha[3]) / alpha[0];
	if (s <= 1e-6 || s >= 1.0 - 1e-6)
		return ;
	if (is->intersect == 0 || alpha[10] < is->dist - 1e-6)
	{
		is->dist = alpha[10];
		is->intersect = 1;
		is->coordinate[0] = l->x[0] * is->dist + l->x[1];
		is->coordinate[1] = l->y[0] * is->dist + l->y[1];
		is->coordinate[2] = l->z[0] * is->dist + l->z[1];
		is->obj_num = num;
	}
}

static void		intersect_cy_sub__2(double alpha[10],
t_intersect *is, t_line *l, int num)
{
	double	s;

	if (alpha[11] <= 0.0)
		return ;
	s = (alpha[2] * alpha[11] + alpha[4] - alpha[3]) / alpha[0];
	if (s <= 1e-6 || s >= 1.0 - 1e-6)
		return ;
	if (is->intersect == 0 || alpha[11] < is->dist - 1e-6)
	{
		is->dist = alpha[11];
		is->intersect = 1;
		is->coordinate[0] = l->x[0] * is->dist + l->x[1];
		is->coordinate[1] = l->y[0] * is->dist + l->y[1];
		is->coordinate[2] = l->z[0] * is->dist + l->z[1];
		is->obj_num = num;
	}
}

void			intersect_cy(t_intersect *is, t_line *l, void *ptr, int num)
{
	double		coef[3];
	double		answer[2];
	double		alpha[12];

	intersect_cy_sub_1(ptr, is, l, num);
	intersect_cy_sub_2(ptr, is, l, num);
	cylinder_coef(coef, alpha, l, ptr);
	if (quadratic_equation(coef, answer) <= 0)
		return ;
	alpha[10] = answer[0];
	alpha[11] = answer[1];
	intersect_cy_sub__1(alpha, is, l, num);
	intersect_cy_sub__2(alpha, is, l, num);
}
