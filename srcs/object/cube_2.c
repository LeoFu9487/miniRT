/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 02:34:24 by yfu               #+#    #+#             */
/*   Updated: 2021/03/03 03:04:16 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	compose_cube_sub(t_square *square, double vector[6][3],
t_cube *cube, int ct)
{
	int	n;

	copy_color(square->color, cube->color);
	square->side_size = cube->side_size;
	copy_vector(square->start_point, vector[ct % 2 + 3]);
	copy_vector(square->orientation, vector[ct / 2]);
	n = 0;
	if (ct / 2 != 0)
		square->vector[n++] =
		make_point(vector[0][0], vector[0][1], vector[0][2]);
	if (ct / 2 != 1)
		square->vector[n++] =
		make_point(vector[1][0], vector[1][1], vector[1][2]);
	if (ct / 2 != 2)
		square->vector[n++] =
		make_point(vector[2][0], vector[2][1], vector[2][2]);
	if (ct % 2)
	{
		modify_length(square->vector[0], -1 * cube->side_size);
		modify_length(square->vector[1], -1 * cube->side_size);
	}
	modify_length(square->orientation, cube->side_size / 2.0);
	if (ct % 2)
		modify_length(square->orientation, -0.5 * cube->side_size);
}

static void	assigned_vector(double vector[6][3], t_cube *cube)
{
	int	ct;

	ct = -1;
	while (++ct < 3)
	{
		vector[ct][0] = 0.0;
		vector[ct][1] = 0.0;
		vector[ct][2] = 0.0;
		vector[ct][ct] = cube->side_size;
		vector[3][ct] = cube->coordinate[ct] - cube->side_size / 2.0;
		vector[4][ct] = cube->coordinate[ct] + cube->side_size / 2.0;
	}
}

void		compose_cube(t_cube *cube)
{
	int			ct;
	t_square	*square;
	double		vector[6][3];
	double		*temp;

	assigned_vector(vector, cube);
	ct = -1;
	while (++ct < 6)
	{
		if (!(cube->square[ct] = init_square()))
			error_exit("compose_cube\n");
		square = cube->square[ct];
		compose_cube_sub(square, vector, cube, ct);
		temp = two_points_vector(square->orientation, cube->coordinate);
		copy_vector(square->coordinate, temp);
		modify_length(square->orientation, -0.5 * cube->side_size);
		ft_free(temp);
	}
}
