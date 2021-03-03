/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 01:30:30 by yfu               #+#    #+#             */
/*   Updated: 2021/03/03 01:31:27 by yfu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	load_images(t_info *info)
{
	t_camera	*camera;
	int			ct;

	info->parse->cur_camera = info->parse->camera;
	while (info->parse->cur_camera)
	{
		camera = info->parse->cur_camera->content;
		ct = -1;
		while (++ct < 17)
		{
			camera->img_ptr[ct] = mlx_new_image(info->mlx_ptr,
			info->parse->rx, info->parse->ry);
			camera->pixel[ct] = (int*)mlx_get_data_addr(camera->img_ptr[ct],
		camera->bits_per_pixel[ct], camera->size_line[ct], camera->endian[ct]);
		}
		ft_putstr_fd("loading camera : ", 2);
		ft_putnbr_fd(camera->num, 2);
		ft_putendl_fd("", 2);
		put_screen(info);
		info->parse->cur_camera = info->parse->cur_camera->next;
	}
}
