/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 19:37:44 by yfu               #+#    #+#             */
/*   Updated: 2021/03/08 01:03:15 by yfu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	parse_fl_sub2(t_flashlight *flashlight, char *str)
{
	int	ct;

	while (*str && ft_isdigit(*str) == 0 && *str != '.')
		str++;
	if (*str == 0)
		error_exit("couldn't find valid brightness for flashlight\n");
	flashlight->brightness = ft_atodouble(&str);
	if (flashlight->brightness < 0.0 || flashlight->brightness > 1.0)
		error_exit("flashlight brightness out of range\n");
	while (*str && ft_isdigit(*str) == 0 && *str != '.')
		str++;
	if (*str == 0)
		error_exit("couldn't find valid diameter for flashlight\n");
	flashlight->diameter = ft_atodouble(&str);
	ct = -1;
	while (++ct < 3)
	{
		while (*str && ft_isdigit(*str) == 0 && *str != '.')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid color for flashlight\n");
		flashlight->color[ct] = (int)ft_atodouble(&str);
		if (flashlight->color[ct] < 0 || flashlight->color[ct] > 255)
			error_exit("flashlight color out of range\n");
	}
}

static void	parse_fl_sub(t_flashlight *flashlight, char *str, int ct)
{
	double	sign;

	ct = -1;
	while (++ct < 3)
	{
		sign = 1.0;
		while (*str && ft_isdigit(*str) == 0 && *str != '.' && *str != '-')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid orientation for flashlight\n");
		if (*str == '-')
		{
			sign *= -1.0;
			if (!ft_isdigit(*(++str)))
				error_exit("find negative number in wrong format\n");
		}
		flashlight->orientation[ct] = sign * ft_atodouble(&str);
		if (flashlight->orientation[ct] < -1.0 ||
		flashlight->orientation[ct] > 1.0)
			error_exit("flashlight orientation out of range\n");
	}
	if (flashlight->orientation[0] == 0.0 && flashlight->orientation[1]
	== 0.0 && flashlight->orientation[2] == 0.0)
		flashlight->orientation[2] = 1.0;
	parse_fl_sub2(flashlight, str);
}

void		parse_fl(t_parse *parse, char *str)
{
	t_flashlight	*flashlight;
	int				ct;
	double			sign;

	flashlight = init_flashlight();
	ft_lstadd_back(&(parse->flashlight), ft_lstnew(flashlight));
	ct = -1;
	while (++ct < 3)
	{
		sign = 1.0;
		while (*str && ft_isdigit(*str) == 0 && *str != '.' && *str != '-')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid coordinate for flashlight\n");
		if (*str == '-')
		{
			sign *= -1.0;
			if (!ft_isdigit(*(++str)))
				error_exit("find negative number in wrong format\n");
		}
		flashlight->coordinate[ct] = sign * ft_atodouble(&str);
	}
	parse_fl_sub(flashlight, str, -1);
}
