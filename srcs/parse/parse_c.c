/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:39:13 by yfu               #+#    #+#             */
/*   Updated: 2021/03/08 00:58:42 by yfu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void			parse_c(t_parse *parse, char *str)
{
	t_camera	*cam_info;
	int			ct;

	cam_info = init_camera();
	ft_lstadd_back(&(parse->camera), ft_lstnew(cam_info));
	ct = -1;
	while (++ct < 3)
		cam_info->coordinate[ct] = ft_neg_double(&str, "coordinate of camera");
	ct = -1;
	while (++ct < 3)
		cam_info->orientation[ct] = ft_neg_double(&str, "camera orientation");
	if (cam_info->orientation[0] == 0.0 && cam_info->orientation[1] == 0.0 &&
	cam_info->orientation[2] == 0.0)
		cam_info->orientation[2] = 1.0;
	if (double_abs(cam_info->orientation[0]) > 1.0 || double_abs(cam_info->
	orientation[1]) > 1.0 || double_abs(cam_info->orientation[2]) > 1.0)
		error_exit("Camera orientation out of range\n");
	while (*str && ft_isdigit(*str) == 0 && *str != '.')
		str++;
	if (*str == 0)
		error_exit("camera vof not found\n");
	cam_info->vof = ft_atodouble(&str);
	if (cam_info->vof < 0.0 || cam_info->vof > 180.0)
		error_exit("camera vof out of range\n");
}
