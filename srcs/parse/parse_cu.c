/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:39:27 by yfu               #+#    #+#             */
/*   Updated: 2021/03/07 19:14:40 by yfu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	parse_cu_sub(t_cube *cube, char *str)
{
	int		ct;

	while (*str && ft_isdigit(*str) == 0 && *str != '.')
		str++;
	if (*str == 0)
		error_exit("couldn't find valid side_size for cube\n");
	cube->side_size = ft_atodouble(&str);
	ct = -1;
	while (++ct < 3)
	{
		while (*str && ft_isdigit(*str) == 0 && *str != '.')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid color for cube\n");
		cube->color[ct] = (int)ft_atodouble(&str);
		if (cube->color[ct] < 0 || cube->color[ct] > 255)
			error_exit("cube color out of range\n");
	}
	compose_cube(cube);
}

void		parse_cu(t_parse *parse, char *str)
{
	t_cube	*cube;
	int		ct;
	double	sign;

	if (!(cube = init_cube()))
		error_exit("parse_cu\n");
	ft_lstadd_back(&(parse->objects), ft_lstnew(init_objects(cu, cube)));
	ct = -1;
	while (++ct < 3)
	{
		sign = 1.0;
		while (*str && ft_isdigit(*str) == 0 && *str != '.' && *str != '-')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid coordinate for cube\n");
		if (*str == '-')
		{
			sign *= -1.0;
			if (!ft_isdigit(*(++str)))
				error_exit("find negative number in wrong format\n");
		}
		cube->coordinate[ct] = sign * ft_atodouble(&str);
	}
	parse_cu_sub(cube, str);
}
