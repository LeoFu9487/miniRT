/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_window_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 01:57:54 by yfu               #+#    #+#             */
/*   Updated: 2021/03/03 02:05:54 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	display_status_sub(t_info *info, t_camera *camera)
{
	if ((info->filter >> 3) & 1)
		ft_putstr_fd(" wave effect : on ", 2);
	else
		ft_putstr_fd(" wave effect : off", 2);
	if ((info->filter >> 2) & 1)
		ft_putstr_fd(" filter R : on ", 2);
	else
		ft_putstr_fd(" filter R : off", 2);
	if ((info->filter >> 1) & 1)
		ft_putstr_fd(" filter G : on ", 1);
	else
		ft_putstr_fd(" filter G : off", 1);
	if ((info->filter >> 0) & 1)
		ft_putstr_fd(" filter B : on ", 2);
	else
		ft_putstr_fd(" filter B : off", 2);
	mlx_put_image_to_window(info->mlx_ptr,
	info->win_ptr, camera->img_ptr[info->filter], 0, 0);
}

static void	display_status(t_info *info, t_camera *camera)
{
	ft_putstr_fd("\rcurrent camera : ", 2);
	ft_putnbr_fd(camera->num, 2);
	if ((info->filter >> 4) & 1)
	{
		ft_putstr_fd(" wearing red-green glasses !", 2);
		ft_putstr_fd("                                      ", 2);
		mlx_put_image_to_window(info->mlx_ptr,
		info->win_ptr, camera->img_ptr[16], 0, 0);
	}
	else
		display_status_sub(info, camera);
}

void		change_camera(t_info *info)
{
	t_parse		*parse;

	parse = info->parse;
	if (parse->cur_camera == NULL || parse->cur_camera->next == NULL)
		parse->cur_camera = parse->camera;
	else
		parse->cur_camera = parse->cur_camera->next;
	display_status(info, parse->cur_camera->content);
}

int			deal_key(int key, void *ptr)
{
	t_info		*info;

	info = ptr;
	if (key == ESC)
		close_program(info);
	if (key == SPACE)
		change_camera(info);
	if (key == _R)
		info->filter ^= 4;
	if (key == G)
		info->filter ^= 2;
	if (key == B)
		info->filter ^= 1;
	if (key == S)
		info->filter ^= 16;
	if (key == W)
		info->filter ^= 8;
	if (!(info->parse->cur_camera))
		return (0);
	display_status(info, info->parse->cur_camera->content);
	return (0);
}
