/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 02:30:34 by yfu               #+#    #+#             */
/*   Updated: 2021/03/08 14:27:28 by yfu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		have_intersection_cu(t_line *l, void *ptr)
{
	int		ct;
	t_cube	*cube;

	ct = -1;
	cube = ptr;
	while (++ct < 6)
		if (have_intersection_sq(l, cube->square[ct]))
			return (1);
	return (0);
}

t_cube	*init_cube(void)
{
	t_cube	*cube;
	int		ct;

	if (!(cube = ft_malloc(1, sizeof(t_cube))))
		error_exit("CUBE\n");
	cube->side_size = -1.0;
	ct = -1;
	while (++ct < 6)
		cube->square[ct] = NULL;
	return (cube);
}

void	intersect_cu(t_intersect *is, t_line *l, void *ptr, int num)
{
	t_cube	*cube;
	int		ct;

	cube = ptr;
	ct = -1;
	while (++ct < 6)
		intersect_sq(is, l, cube->square[ct], num);
}

double	*normal_vector_cu(double *point, void *ptr)
{
	double	*ans;
	t_cube	*cube;
	int		ct;

	cube = ptr;
	if (!(ans = ft_malloc(3, sizeof(double))))
		error_exit("normal_vector_cu\n");
	ct = -1;
	while (++ct < 6)
	{
		if (double_abs(dot(cube->square[ct]->coordinate,
		cube->square[ct]->orientation) -
		dot(cube->square[ct]->orientation, point)) < 1e-6)
			copy_vector(ans, cube->square[ct]->orientation);
	}
	return (ans);
}
