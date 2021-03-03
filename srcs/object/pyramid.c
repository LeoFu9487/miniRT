/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 02:18:40 by yfu               #+#    #+#             */
/*   Updated: 2021/03/03 02:18:54 by yfu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pyramid		*init_pyramid(void)
{
	t_pyramid	*pyramid;

	if (!(pyramid = ft_malloc(1, sizeof(t_pyramid))))
		error_exit("init_pyramid\n");
	return (pyramid);
}

void			intersect_py(t_intersect *is, t_line *l, void *ptr, int num)
{
	int			ct;
	t_pyramid	*pyramid;

	pyramid = ptr;
	intersect_sq(is, l, pyramid->square, num);
	ct = -1;
	while (++ct < 4)
		intersect_tr(is, l, pyramid->triangle[ct], num);
}

int				have_intersection_py(t_line *l, void *ptr)
{
	int			ct;
	t_pyramid	*pyramid;

	pyramid = ptr;
	if (have_intersection_sq(l, pyramid->square))
		return (1);
	ct = -1;
	while (++ct < 4)
		if (have_intersection_tr(l, pyramid->triangle[ct]))
			return (1);
	return (0);
}

double			*normal_vector_py(double *point, void *ptr)
{
	t_pyramid	*pyramid;
	t_square	*square;
	t_triangle	*triangle;
	int			ct;
	double		*ans;

	pyramid = ptr;
	square = pyramid->square;
	if (!(ans = ft_malloc(3, sizeof(double))))
		error_exit("normal_vector_py\n");
	if (double_abs(dot(square->orientation, square->coordinate)
	- dot(square->orientation, point)) < 1e-6)
		copy_vector(ans, square->orientation);
	ct = -1;
	while (++ct < 4)
	{
		triangle = pyramid->triangle[ct];
		if (double_abs(dot(triangle->orientation, triangle->point[0])
		- dot(triangle->orientation, point)) < 1e-6)
			copy_vector(ans, triangle->orientation);
	}
	return (ans);
}
