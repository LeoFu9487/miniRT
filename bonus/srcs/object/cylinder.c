/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 19:21:44 by yfu               #+#    #+#             */
/*   Updated: 2021/03/08 14:27:38 by yfu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cylinder		*init_cylinder(void)
{
	t_cylinder	*cylinder;
	int			ct;

	if (!(cylinder = ft_malloc(1, sizeof(t_cylinder))))
		error_exit("CYLINDER\n");
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

static void		cylinder_coef_sub(double *coef, double *alpha,
t_cylinder *cylinder)
{
	coef[0] = -1.0 * alpha[2] * alpha[2] / alpha[0] + alpha[1];
	coef[1] = 2.0 * alpha[2] * (alpha[3] - alpha[4]) / alpha[0]
	+ 2.0 * (alpha[6] - alpha[5]);
	coef[2] = -1.0 * (alpha[4] - alpha[3]) * (alpha[4] - alpha[3])
	/ alpha[0] + alpha[7] + alpha[8] - 2 * alpha[9] - cylinder->diameter
	* cylinder->diameter / 4.0;
}

void			cylinder_coef(double *coef, double *alpha, t_line *l,
t_cylinder *cylinder)
{
	double	p[2][3];
	double	v[2][3];

	copy_vector(p[0], cylinder->end_point[0]);
	p[1][0] = l->x[1];
	p[1][1] = l->y[1];
	p[1][2] = l->z[1];
	copy_vector(v[0], cylinder->orientation);
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
	cylinder_coef_sub(coef, alpha, cylinder);
}

double			*normal_vector_cy(double *point, void *ptr)
{
	t_cylinder	*cylinder;
	double		*ans;
	double		*vector[2];

	cylinder = ptr;
	if (double_abs(dot(cylinder->orientation, point) -
	dot(cylinder->orientation, cylinder->end_point[0])) < 1e-6 ||
	double_abs(dot(cylinder->orientation, point) - dot(cylinder->orientation,
	cylinder->end_point[1])) < 1e-6)
	{
		if (!(ans = ft_malloc(3, sizeof(double))))
			error_exit("normal_vector_cy\n");
		ans[0] = cylinder->orientation[0];
		ans[1] = cylinder->orientation[1];
		ans[2] = cylinder->orientation[2];
	}
	else
	{
		vector[0] = two_points_vector(cylinder->end_point[0], point);
		vector[1] = cross(vector[0], cylinder->orientation);
		ans = cross(cylinder->orientation, vector[1]);
		ft_free(vector[0]);
		ft_free(vector[1]);
	}
	return (ans);
}
