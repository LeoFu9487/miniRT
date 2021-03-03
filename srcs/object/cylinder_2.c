/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 19:22:13 by yfu               #+#    #+#             */
/*   Updated: 2021/03/03 21:34:34 by yfu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void			assign_v(double v[3][3], t_line *l)
{
	v[0][0] = l->x[1];
	v[0][1] = l->y[1];
	v[0][2] = l->z[1];
	v[1][0] = l->x[0];
	v[1][1] = l->y[0];
	v[1][2] = l->z[0];
}

static int		have_intersection_cy_sub(t_cylinder *cylinder,
double v[3][3], int ct)
{
	double	s;

	s = (dot(cylinder->orientation, cylinder->end_point[ct]) -
	dot(cylinder->orientation, (double*)v[0])) / dot(cylinder->orientation,
	(double*)v[1]);
	if (s <= 1e-6 || s >= 1.0 - 1e-6)
		return (0);
	v[2][0] = v[0][0] + v[1][0] * s;
	v[2][1] = v[0][1] + v[1][1] * s;
	v[2][2] = v[0][2] + v[1][2] * s;
	if (two_points_distance((double*)v[2], (double*)(cylinder->end_point[ct]))
	<= cylinder->diameter / 2.0)
		return (1);
	return (0);
}

int				have_intersection_cy(t_line *l, void *ptr)
{
	double		coef[3];
	double		answer[2];
	double		alpha[10];
	double		v[3][3];

	assign_v(v, l);
	if (have_intersection_cy_sub(ptr, v, 0) ||
	have_intersection_cy_sub(ptr, v, 1))
		return (1);
	cylinder_coef(coef, alpha, l, ptr);
	if (quadratic_equation(coef, answer) <= 0)
		return (0);
	if (answer[0] > 1e-6 && answer[0] < 1.0 - 1e-6 && (alpha[2] * answer[0]
	+ alpha[4] - alpha[3]) / alpha[0] > 1e-6 && (alpha[2] * answer[0] + alpha[4]
	- alpha[3]) / alpha[0] < 1.0 - 1e-6)
		return (1);
	if (answer[1] > 1e-6 && answer[1] < 1.0 - 1e-6 && (alpha[2] * answer[1] +
	alpha[4] - alpha[3]) / alpha[0] > 1e-6 && (alpha[2] * answer[1] + alpha[4]
	- alpha[3]) / alpha[0] < 1.0 - 1e-6)
		return (1);
	return (0);
}
