/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:39:34 by yfu               #+#    #+#             */
/*   Updated: 2021/03/07 19:36:23 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	parse_cy_sub3(t_cylinder *cylinder)
{
	modify_length(cylinder->orientation, cylinder->height / 2.0);
	cylinder->end_point[1] =
	two_points_vector(cylinder->orientation, cylinder->coordinate);
	modify_length(cylinder->orientation, -1.0 * cylinder->height);
	cylinder->end_point[0] =
	two_points_vector(cylinder->orientation, cylinder->end_point[1]);
	cylinder->middle_line =
	two_points_line(cylinder->end_point[0], cylinder->end_point[1]);
}

static void	parse_cy_sub2(t_cylinder *cylinder, char *str)
{
	int	ct;

	while (*str && ft_isdigit(*str) == 0 && *str != '.')
		str++;
	if (*str == 0)
		error_exit("couldn't find valid diameter for cylinder\n");
	cylinder->diameter = ft_atodouble(&str);
	while (*str && ft_isdigit(*str) == 0 && *str != '.')
		str++;
	if (*str == 0)
		error_exit("couldn't find valid height for cylinder\n");
	cylinder->height = ft_atodouble(&str);
	ct = -1;
	while (++ct < 3)
	{
		while (*str && ft_isdigit(*str) == 0 && *str != '.')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid color for cylinder\n");
		cylinder->color[ct] = (int)ft_atodouble(&str);
		if (cylinder->color[ct] < 0 || cylinder->color[ct] > 255)
			error_exit("Cylinder color out of range\n");
	}
	parse_cy_sub3(cylinder);
}

static void	parse_cy_sub(t_cylinder *cylinder, char *str)
{
	int		ct;
	double	sign;

	ct = -1;
	while (++ct < 3)
	{
		sign = 1.0;
		while (*str && ft_isdigit(*str) == 0 && *str != '.' && *str != '-')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid orientation for cylinder\n");
		if (*str == '-')
		{
			sign *= -1.0;
			if (!ft_isdigit(*(++str)))
				error_exit("find negative number in wrong format\n");
		}
		cylinder->orientation[ct] = sign * ft_atodouble(&str);
		if (cylinder->orientation[ct] < -1.0 || cylinder->orientation[ct] > 1.0)
			error_exit("Cylinder orientation out of range\n");
	}
	if (cylinder->orientation[0] == 0.0 && cylinder->orientation[1] == 0.0)
		cylinder->orientation[2] = 1.0;
	parse_cy_sub2(cylinder, str);
}

void		parse_cy(t_parse *parse, char *str)
{
	t_cylinder	*cylinder;
	int			ct;
	double		sign;

	cylinder = init_cylinder();
	ft_lstadd_back(&(parse->objects), ft_lstnew(init_objects(cy, cylinder)));
	ct = -1;
	while (++ct < 3)
	{
		sign = 1.0;
		while (*str && ft_isdigit(*str) == 0 && *str != '.' && *str != '-')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid coordinate for cylinder\n");
		if (*str == '-')
		{
			sign *= -1.0;
			if (!ft_isdigit(*(++str)))
				error_exit("find negative number in wrong format\n");
		}
		cylinder->coordinate[ct] = sign * ft_atodouble(&str);
	}
	parse_cy_sub(cylinder, str);
}
