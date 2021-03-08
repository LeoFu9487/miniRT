/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_co.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:39:20 by yfu               #+#    #+#             */
/*   Updated: 2021/03/07 19:11:05 by yfu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	parse_co_sub2(t_cone *cone)
{
	modify_length(cone->orientation, cone->height / 2.0);
	cone->end_point[1] = two_points_vector(cone->orientation, cone->coordinate);
	modify_length(cone->orientation, -1.0 * cone->height);
	cone->end_point[0] = two_points_vector(cone->orientation,
	cone->end_point[1]);
}

static void	parse_co_sub1(t_cone *cone, char *str)
{
	int	ct;

	while (*str && ft_isdigit(*str) == 0 && *str != '.')
		str++;
	if (*str == 0)
		error_exit("couldn't find valid diameter for cone\n");
	cone->diameter = ft_atodouble(&str);
	while (*str && ft_isdigit(*str) == 0 && *str != '.')
		str++;
	if (*str == 0)
		error_exit("couldn't find valid height for cone\n");
	cone->height = ft_atodouble(&str);
	ct = -1;
	while (++ct < 3)
	{
		while (*str && ft_isdigit(*str) == 0 && *str != '.')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid color for cone\n");
		cone->color[ct] = (int)ft_atodouble(&str);
		if (cone->color[ct] < 0 || cone->color[ct] > 255)
			error_exit("Cone color out of range\n");
	}
	parse_co_sub2(cone);
}

static void	parse_co_sub(t_cone *cone, char *str)
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
			error_exit("couldn't find valid orientation for cone\n");
		if (*str == '-')
		{
			sign *= -1.0;
			if (!ft_isdigit(*(++str)))
				error_exit("find negative number in wrong format\n");
		}
		cone->orientation[ct] = sign * ft_atodouble(&str);
		if (cone->orientation[ct] < -1.0 || cone->orientation[ct] > 1.0)
			error_exit("Cone orientation out of range\n");
	}
	if (cone->orientation[0] == 0.0 && cone->orientation[1] == 0.0)
		cone->orientation[2] = 1.0;
	parse_co_sub1(cone, str);
}

void		parse_co(t_parse *parse, char *str)
{
	t_cone		*cone;
	int			ct;
	double		sign;

	cone = init_cone();
	ft_lstadd_back(&(parse->objects), ft_lstnew(init_objects(co, cone)));
	ct = -1;
	while (++ct < 3)
	{
		sign = 1.0;
		while (*str && ft_isdigit(*str) == 0 && *str != '.' && *str != '-')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid coordinate for coner\n");
		if (*str == '-')
		{
			sign *= -1.0;
			if (!ft_isdigit(*(++str)))
				error_exit("find negative number in wrong format\n");
		}
		cone->coordinate[ct] = sign * ft_atodouble(&str);
	}
	parse_co_sub(cone, str);
}
