/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 03:14:53 by yfu               #+#    #+#             */
/*   Updated: 2021/03/08 14:27:22 by yfu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cone			*init_cone(void)
{
	t_cone		*cone;
	int			ct;

	if (!(cone = ft_malloc(1, sizeof(t_cone))))
		error_exit("CONE\n");
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

static void		cone_coef_sub(double *coef, double *alpha, t_cone *cone)
{
	coef[0] = -1.0 * alpha[2] * alpha[2] / alpha[0] + alpha[1] - cone->diameter
	* cone->diameter * alpha[2] * alpha[2] / (4.0 * alpha[0] * alpha[0]);
	coef[1] = 2.0 * alpha[2] * (alpha[3] - alpha[4]) / alpha[0] + 2.0 *
	(alpha[6] - alpha[5]) + cone->diameter * cone->diameter * alpha[2] *
	(alpha[0] + alpha[3] - alpha[4]) / (2.0 * alpha[0] * alpha[0]);
	coef[2] = -1.0 * (alpha[4] - alpha[3]) * (alpha[4] - alpha[3]) / alpha[0]
	+ alpha[7] + alpha[8] - 2 * alpha[9] - cone->diameter * cone->diameter *
	(alpha[4] - alpha[3]) * (alpha[4] - alpha[3]) / (4.0 * alpha[0] * alpha[0])
	+ cone->diameter * cone->diameter * (alpha[4] - alpha[3]) / (2.0 * alpha[0])
	- cone->diameter * cone->diameter / 4.0;
}

void			cone_coef(double *coef, double *alpha, t_line *l, t_cone *cone)
{
	double	p[2][3];
	double	v[2][3];

	copy_vector(p[0], cone->end_point[0]);
	p[1][0] = l->x[1];
	p[1][1] = l->y[1];
	p[1][2] = l->z[1];
	copy_vector(v[0], cone->orientation);
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
	cone_coef_sub(coef, alpha, cone);
}

double			*normal_vector_co(double *point, void *ptr)
{
	t_cone		*cone;
	double		*ans;
	double		*vector[3];

	cone = ptr;
	if (double_abs(dot(cone->orientation, point) -
	dot(cone->orientation, cone->end_point[0])) < 1e-6)
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
