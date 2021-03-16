/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:39:55 by yfu               #+#    #+#             */
/*   Updated: 2021/03/08 00:04:37 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	parse_pl_sub2(t_plane *plane, char *str)
{
	int	ct;

	ct = -1;
	while (++ct < 3)
	{
		while (*str && ft_isdigit(*str) == 0 && *str != '.')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid color for plane\n");
		plane->color[ct] = (int)ft_atodouble(&str);
		if (plane->color[ct] < 0 || plane->color[ct] > 255)
			error_exit("Plane color out of range\n");
	}
}

static void	parse_pl_sub(t_plane *plane, char *str)
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
			error_exit("couldn't find valid orientation for plane\n");
		if (*str == '-')
		{
			sign *= -1.0;
			if (!ft_isdigit(*(++str)))
				error_exit("find negative number in wrong format\n");
		}
		plane->orientation[ct] = sign * ft_atodouble(&str);
		if (plane->orientation[ct] < -1.0 ||
		plane->orientation[ct] > 1.0)
			error_exit("Plane orientation out of range\n");
	}
	if (plane->orientation[0] == 0.0 && plane->orientation[1] == 0.0)
		plane->orientation[2] = 1.0;
	parse_pl_sub2(plane, str);
}

void		parse_pl(t_parse *parse, char *str)
{
	t_plane	*plane;
	int		ct;
	double	sign;

	plane = init_plane();
	ft_lstadd_back(&(parse->objects), ft_lstnew(init_objects(pl, plane)));
	ct = -1;
	while (++ct < 3)
	{
		sign = 1.0;
		while (*str && ft_isdigit(*str) == 0 && *str != '.' && *str != '-')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid orientation for plane\n");
		if (*str == '-')
		{
			sign *= -1.0;
			if (!ft_isdigit(*(++str)))
				error_exit("find negative number in wrong format\n");
		}
		plane->coordinate[ct] = sign * ft_atodouble(&str);
	}
	parse_pl_sub(plane, str);
}
