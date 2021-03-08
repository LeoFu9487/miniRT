/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 02:12:53 by yfu               #+#    #+#             */
/*   Updated: 2021/03/08 14:28:45 by yfu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	*init_sphere(void)
{
	int			cnt;
	t_sphere	*sphere;

	if (!(sphere = ft_malloc(1, sizeof(t_sphere))))
		error_exit("SPHERE\n");
	cnt = -1;
	while (++cnt < 3)
		sphere->coordinate[cnt] = 0.0;
	sphere->diameter = 0.0;
	cnt = -1;
	while (++cnt < 3)
		sphere->color[cnt] = 0;
	return (sphere);
}

static void	coef_sp(t_line *l, t_sphere *sphere, double coef[3])
{
	coef[0] = l->x[0] * l->x[0] + l->y[0] * l->y[0] + l->z[0] * l->z[0];
	coef[1] = 2.0 * (l->x[0] * (l->x[1] - sphere->coordinate[0]) +
	l->y[0] * (l->y[1] - sphere->coordinate[1]) + l->z[0]
	* (l->z[1] - sphere->coordinate[2]));
	coef[2] = (l->x[1] - sphere->coordinate[0]) * (l->x[1] -
	sphere->coordinate[0]) + (l->y[1] - sphere->coordinate[1]) * (l->y[1]
	- sphere->coordinate[1]) + (l->z[1] - sphere->coordinate[2]) * (l->z[1]
	- sphere->coordinate[2]) - (sphere->diameter / 2.0) *
	(sphere->diameter / 2.0);
}

void		intersect_sp(t_intersect *is, t_line *l, void *ptr, int num)
{
	t_sphere	*sphere;
	double		answer[2];
	double		coef[3];
	int			ct;

	sphere = (t_sphere*)ptr;
	coef_sp(l, sphere, coef);
	if (quadratic_equation(coef, answer) <= 0)
		return ;
	ct = -1;
	while (++ct < 2)
	{
		if (answer[ct] < 0.0)
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

int			have_intersection_sp(t_line *l, void *ptr)
{
	t_sphere	*sphere;
	double		coef[3];
	double		answer[2];

	sphere = (t_sphere*)ptr;
	coef[0] = l->x[0] * l->x[0] + l->y[0] * l->y[0] + l->z[0] * l->z[0];
	coef[1] = 2.0 * (l->x[0] * (l->x[1] - sphere->coordinate[0]) + l->y[0]
	* (l->y[1] - sphere->coordinate[1]) + l->z[0] *
	(l->z[1] - sphere->coordinate[2]));
	coef[2] = (l->x[1] - sphere->coordinate[0]) * (l->x[1] -
	sphere->coordinate[0]) + (l->y[1] - sphere->coordinate[1]) * (l->y[1]
	- sphere->coordinate[1]) + (l->z[1] - sphere->coordinate[2]) * (l->z[1]
	- sphere->coordinate[2]) - (sphere->diameter / 2.0) *
	(sphere->diameter / 2.0);
	if (quadratic_equation(coef, answer) <= 0)
		return (0);
	if (answer[0] > 1e-6 && answer[0] < 1.0 - 1e-6)
		return (1);
	return ((answer[1] > 1e-6 && answer[1] < 1.0 - 1e-6) ? 1 : 0);
}

double		*normal_vector_sp(double *point, void *ptr)
{
	t_sphere	*sphere;

	sphere = (t_sphere*)ptr;
	return (two_points_vector(point, sphere->coordinate));
}
