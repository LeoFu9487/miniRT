/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_r.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:40:09 by yfu               #+#    #+#             */
/*   Updated: 2021/03/07 18:40:14 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void			parse_r(t_parse *parse, char *str)
{
	if (parse->rx || parse->ry)
		error_exit("Define render size multiple times!\n");
	parse->rx = (int)ft_atodouble(&str);
	parse->ry = (int)ft_atodouble(&str);
	if (parse->rx <= 0 || parse->ry <= 0)
		error_exit("invalid rendering size\n");
}
