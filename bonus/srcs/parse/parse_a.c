/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:38:53 by yfu               #+#    #+#             */
/*   Updated: 2021/03/07 18:39:00 by yfu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void			parse_a(t_parse *parse, char *str)
{
	int		cnt;

	if (parse->aratio != -1.0 || parse->acolor[0] != -1 ||
	parse->acolor[1] != -1 || parse->acolor[2] != -1)
		error_exit("Define Ambient lighting multiple times\n");
	while (*str && ft_isdigit(*str) == 0 && *str != '.')
		str++;
	if (*str == 0)
		error_exit("Ambient lighting ratio not found\n");
	parse->aratio = ft_atodouble(&str);
	if (parse->aratio < 0.0 || parse->aratio > 1.0)
		error_exit("Ambient lighting ratio invalid\n");
	cnt = -1;
	while (++cnt < 3)
	{
		while (*str && ft_isdigit(*str) == 0 && *str != '.')
			str++;
		if (*str == 0)
			error_exit("Ambient lighting color not found\n");
		parse->acolor[cnt] = (int)ft_atodouble(&str);
		if (parse->acolor[cnt] < 0 || parse->acolor[cnt] > 255)
			error_exit("Ambient lighting color invalid\n");
	}
}
