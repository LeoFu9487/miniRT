/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sq.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:40:22 by yfu               #+#    #+#             */
/*   Updated: 2021/03/08 00:51:24 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	parse_sq_sub3(t_square *square)
{
	double	base_v[3];
	int		ct;

	base_v[0] = 0.0;
	if (square->orientation[1] == 0.0 && square->orientation[0] == 0.0)
		base_v[1] = 1.0;
	else
		base_v[1] = 0.0;
	base_v[2] = 1.0 - base_v[1];
	square->vector[0] = cross(base_v, square->orientation);
	square->vector[1] = cross(square->vector[0], square->orientation);
	modify_length(square->vector[0], square->side_size);
	modify_length(square->vector[1], square->side_size);
	ct = -1;
	while (++ct < 3)
		square->start_point[ct] = square->coordinate[ct] -
		square->vector[0][ct] / 2.0 - square->vector[1][ct] / 2.0;
}

static void	parse_sq_sub2(t_square *square, char *str)
{
	int		ct;

	if (*str == 0)
		error_exit("couldn't find valid side_size for square\n");
	square->side_size = ft_atodouble(&str);
	ct = -1;
	while (++ct < 3)
	{
		while (*str && ft_isdigit(*str) == 0 && *str != '.')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid color for square\n");
		square->color[ct] = (int)ft_atodouble(&str);
		if (square->color[ct] < 0 || square->color[ct] > 255)
			error_exit("Square color out of range\n");
	}
	parse_sq_sub3(square);
}

static void	parse_sq_sub(t_square *square, char *str, int ct)
{
	double	sign;

	while (++ct < 3)
	{
		sign = 1.0;
		while (*str && ft_isdigit(*str) == 0 && *str != '.' && *str != '-')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid orientation for square\n");
		if (*str == '-')
		{
			sign *= -1.0;
			if (!ft_isdigit(*(++str)))
				error_exit("find negative number in wrong format\n");
		}
		square->orientation[ct] = sign * ft_atodouble(&str);
		if (square->orientation[ct] < -1.0 || square->orientation[ct] > 1.0)
			error_exit("Square orientation out of range\n");
	}
	if (square->orientation[0] == 0.0 && square->orientation[1] == 0.0)
		square->orientation[2] = 1.0;
	while (*str && ft_isdigit(*str) == 0 && *str != '.')
		str++;
	parse_sq_sub2(square, str);
}

void		parse_sq(t_parse *parse, char *str)
{
	t_square	*square;
	int			ct;
	double		sign;

	square = init_square();
	ft_lstadd_back(&(parse->objects), ft_lstnew(init_objects(sq, square)));
	ct = -1;
	while (++ct < 3)
	{
		sign = 1.0;
		while (*str && ft_isdigit(*str) == 0 && *str != '.' && *str != '-')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid coordinate for square\n");
		if (*str == '-')
		{
			sign *= -1.0;
			if (!ft_isdigit(*(++str)))
				error_exit("find negative number in wrong format\n");
		}
		square->coordinate[ct] = sign * ft_atodouble(&str);
	}
	parse_sq_sub(square, str, -1);
}
