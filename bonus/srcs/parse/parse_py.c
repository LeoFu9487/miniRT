/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_py.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:40:01 by yfu               #+#    #+#             */
/*   Updated: 2021/03/08 01:09:47 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	parse_py_sub4(t_pyramid *pyramid, t_square *square,
double *top_point, double *point[4])
{
	int	ct;

	ct = -1;
	while (++ct < 4)
	{
		if (!(pyramid->triangle[ct] = init_triangle()))
			error_exit("parse_pyramid/init_triangle");
		copy_color(pyramid->triangle[ct]->color, square->color);
		copy_vector(pyramid->triangle[ct]->point[0], top_point);
		copy_vector(pyramid->triangle[ct]->point[1], point[ct]);
		copy_vector(pyramid->triangle[ct]->point[2], point[(ct + 1) % 4]);
		pyramid->triangle[ct]->vector[0] = two_points_vector(
		pyramid->triangle[ct]->point[0], pyramid->triangle[ct]->point[1]);
		pyramid->triangle[ct]->vector[1] = two_points_vector(
		pyramid->triangle[ct]->point[0], pyramid->triangle[ct]->point[2]);
		pyramid->triangle[ct]->orientation = cross(
		pyramid->triangle[ct]->vector[0], pyramid->triangle[ct]->vector[1]);
		if (pyramid->triangle[ct]->orientation[0] == 0.0 && pyramid->
triangle[ct]->orientation[1] == 0.0 && pyramid->triangle[ct]->
orientation[2] == 0.0)
			error_exit("invalid points of triangle in pyramid : form a line\n");
	}
	ct = -1;
	while (++ct < 4)
		ft_free(point[ct]);
}

static void	parse_py_sub3(t_pyramid *p,
double base_v[3], double height, int ct)
{
	double		*top_point;
	double		*point[4];

	if (p->square->orientation[1] == 0.0 && p->square->orientation[0] == 0.0)
		base_v[1] = 1.0;
	else
		base_v[1] = 0.0;
	base_v[2] = 1.0 - base_v[1];
	p->square->vector[0] = cross(base_v, p->square->orientation);
	p->square->vector[1] = cross(p->square->vector[0], p->square->orientation);
	modify_length(p->square->vector[0], p->square->side_size);
	modify_length(p->square->vector[1], p->square->side_size);
	while (++ct < 3)
		p->square->start_point[ct] = p->square->coordinate[ct] -
		p->square->vector[0][ct] / 2.0 - p->square->vector[1][ct] / 2.0;
	modify_length(p->square->orientation, height);
	top_point = add_vector(p->square->orientation, p->square->coordinate);
	ct = -1;
	point[0] = make_point(p->square->start_point[0],
	p->square->start_point[1], p->square->start_point[2]);
	point[1] = add_vector(point[0], p->square->vector[0]);
	point[2] = add_vector(point[1], p->square->vector[1]);
	point[3] = add_vector(point[0], p->square->vector[1]);
	parse_py_sub4(p, p->square, top_point, point);
}

static void	parse_py_sub2(t_pyramid *pyramid, char *str, t_square *square)
{
	int			ct;
	double		height;
	double		base_v[3];

	if (*str == 0)
		error_exit("couldn't find valid side_size for pyramid\n");
	square->side_size = ft_atodouble(&str);
	while (*str && ft_isdigit(*str) == 0 && *str != '.')
		str++;
	if (*str == 0)
		error_exit("couldn't find valid height for pyramid\n");
	height = ft_atodouble(&str);
	ct = -1;
	while (++ct < 3)
	{
		while (*str && ft_isdigit(*str) == 0 && *str != '.')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid color for pyramid\n");
		square->color[ct] = (int)ft_atodouble(&str);
		if (square->color[ct] < 0 || square->color[ct] > 255)
			error_exit("Square color out of range\n");
	}
	base_v[0] = 0.0;
	parse_py_sub3(pyramid, base_v, height, -1);
}

static void	parse_py_sub(t_pyramid *pyramid, char *str,
t_square *square, int ct)
{
	double		sign;

	while (++ct < 3)
	{
		sign = 1.0;
		while (*str && ft_isdigit(*str) == 0 && *str != '.' && *str != '-')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid orientation for pyramid\n");
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
	parse_py_sub2(pyramid, str, square);
}

void		parse_py(t_parse *parse, char *str)
{
	t_pyramid	*pyramid;
	int			ct;
	double		sign;

	pyramid = init_pyramid();
	pyramid->square = init_square();
	ft_lstadd_back(&(parse->objects), ft_lstnew(init_objects(py, pyramid)));
	ct = -1;
	while (++ct < 3)
	{
		sign = 1.0;
		while (*str && ft_isdigit(*str) == 0 && *str != '.' && *str != '-')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid coordinate for pyramid\n");
		if (*str == '-')
		{
			sign *= -1.0;
			if (!ft_isdigit(*(++str)))
				error_exit("find negative number in wrong format\n");
		}
		pyramid->square->coordinate[ct] = sign * ft_atodouble(&str);
	}
	parse_py_sub(pyramid, str, pyramid->square, -1);
}
