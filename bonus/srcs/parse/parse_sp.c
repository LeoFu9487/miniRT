/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:40:17 by yfu               #+#    #+#             */
/*   Updated: 2021/03/08 00:08:33 by yfu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	parse_sp_sub(t_sphere *sphere, char *str)
{
	int	ct;

	while (*str && ft_isdigit(*str) == 0 && *str != '.')
		str++;
	if (*str == 0)
		error_exit("couldn't find valid diameter for sphere\n");
	sphere->diameter = ft_atodouble(&str);
	ct = -1;
	if (sphere->diameter < 0.0)
		error_exit("negative diameter for sphere\n");
	while (++ct < 3)
	{
		while (*str && ft_isdigit(*str) == 0 && *str != '.')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid color for sphere\n");
		sphere->color[ct] = (int)ft_atodouble(&str);
		if (sphere->color[ct] < 0 || sphere->color[ct] > 255)
			error_exit("sphere color out of range\n");
	}
}

void		parse_sp(t_parse *parse, char *str)
{
	t_sphere	*sphere;
	int			ct;
	double		sign;

	sphere = init_sphere();
	ft_lstadd_back(&(parse->objects), ft_lstnew(init_objects(sp, sphere)));
	ct = -1;
	while (++ct < 3)
	{
		sign = 1.0;
		while (*str && ft_isdigit(*str) == 0 && *str != '.' && *str != '-')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid orientation for sphere\n");
		if (*str == '-')
		{
			sign *= -1.0;
			if (!ft_isdigit(*(++str)))
				error_exit("find negative number in wrong format\n");
		}
		sphere->coordinate[ct] = sign * ft_atodouble(&str);
	}
	parse_sp_sub(sphere, str);
}
