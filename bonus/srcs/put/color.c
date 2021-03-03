/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 01:30:09 by yfu               #+#    #+#             */
/*   Updated: 2021/03/03 01:30:15 by yfu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		get_color(int *rgb)
{
	return (rgb[0] * 256 * 256 + rgb[1] * 256 + rgb[2]);
}
