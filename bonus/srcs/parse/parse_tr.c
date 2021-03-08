/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:40:29 by yfu               #+#    #+#             */
/*   Updated: 2021/03/07 19:33:58 by yfu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static char	*parse_tr_sub(t_triangle *triangle, char *str, int ct[2])
{
	double	sign;

	sign = 1.0;
	while (*str && ft_isdigit(*str) == 0 && *str != '.' && *str != '-')
		str++;
	if (*str == 0)
		error_exit("couldn't find valid coordinate for triangle\n");
	if (*str == '-')
	{
		sign *= -1.0;
		if (!ft_isdigit(*(++str)))
			error_exit("find negative number in wrong format\n");
	}
	triangle->point[ct[0]][ct[1]] = sign * ft_atodouble(&str);
	return (str);
}

static void	parse_tr_sub1(t_triangle *triangle)
{
	triangle->vector[0] =
	two_points_vector(triangle->point[0], triangle->point[1]);
	triangle->vector[1] =
	two_points_vector(triangle->point[0], triangle->point[2]);
	if (!(triangle->orientation =
	cross(triangle->vector[0], triangle->vector[1])))
		error_exit("parse_tr\n");
	if (triangle->orientation[0] == 0.0 &&
	triangle->orientation[1] == 0.0
	&& triangle->orientation[2] == 0.0)
		error_exit("invalid points of triangle : form a line\n");
}

void		parse_tr(t_parse *parse, char *str)
{
	t_triangle	*triangle;
	int			ct[2];

	triangle = init_triangle();
	ft_lstadd_back(&(parse->objects), ft_lstnew(init_objects(tr, triangle)));
	ct[0] = -1;
	while (++ct[0] < 3)
	{
		ct[1] = -1;
		while (++ct[1] < 3)
			str = parse_tr_sub(triangle, str, ct);
	}
	ct[0] = -1;
	while (++ct[0] < 3)
	{
		while (*str && ft_isdigit(*str) == 0 && *str != '.')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid color for triangle\n");
		triangle->color[ct[0]] = (int)ft_atodouble(&str);
		if (triangle->color[ct[0]] < 0 || triangle->color[ct[0]] > 255)
			error_exit("triangle color out of range\n");
	}
	parse_tr_sub1(triangle);
}
