/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:39:46 by yfu               #+#    #+#             */
/*   Updated: 2021/03/07 23:50:28 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void		parse_l_sub(t_light *light, char *str)
{
	int	ct;

	ct = -1;
	if (light->brightness < 0.0 || light->brightness > 1.0)
		error_exit("brightness of light out of range\n");
	while (++ct < 3)
	{
		while (*str && ft_isdigit(*str) == 0 && *str != '.')
			str++;
		if (*str == 0)
			error_exit("color for light not found\n");
		light->color[ct] = (int)ft_atodouble(&str);
		if (light->color[ct] < 0 || light->color[ct] > 255)
			error_exit("Light color out of range\n");
	}
}

void			parse_l(t_parse *parse, char *str)
{
	t_light		*light;
	int			ct;

	light = init_light();
	ft_lstadd_front(&(parse->light), ft_lstnew(light));
	ct = -1;
	while (++ct < 3)
		light->coordinate[ct] = ft_neg_double(&str, "coordinate of light");
	while (*str && ft_isdigit(*str) == 0 && *str != '.')
		str++;
	if (*str == 0)
		error_exit("brightness for light not found\n");
	light->brightness = ft_atodouble(&str);
	parse_l_sub(light, str);
}
