/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_screen_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 20:22:28 by yfu               #+#    #+#             */
/*   Updated: 2021/03/02 22:33:32 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		clean_screen(t_info *info)
{
	int	pixel[2];

	pixel[0] = -1;
	while (++pixel[0] < info->parse->rx)
	{
		pixel[1] = -1;
		while (++pixel[1] < info->parse->ry)
			mlx_pixel_put(info->mlx_ptr, info->win_ptr, pixel[0], pixel[1], 0);
	}
}

void		put_screen(t_info *info)
{
	t_camera	*camera;

	if (info->parse->cur_camera == NULL)
		error_exit("Camera not found !! cannot put_screen\n");
	camera = (t_camera*)(info->parse->cur_camera->content);
	if (camera->vof > 170.0)
		camera->vof = 170.0;
	if (camera->vof < 1.0)
		camera->vof = 1.0;
	if (camera->distance_to_screen == 0.0)
		camera->distance_to_screen =
		((double)info->parse->rx) / 2.0 / tan(camera->vof / 2.0 * M_PI / 180.0);
	put_all(info);
}

static void	get_intersect_sub(int color[3], int *pixel,
						t_info *info, double *vector[2])
{
	t_line		*line;
	double		position[2];
	t_intersect	*intersect;

	position[0] = (double)pixel[0] - (double)(info->parse->rx) / 2.0;
	position[1] = (double)pixel[1] - (double)(info->parse->ry) / 2.0;
	if (!(line = new_line(info->parse->cur_camera->content,
							vector[0], vector[1], position)))
		error_exit("get_intersect_sub_1\n");
	if (!(intersect = init_intersect(info->parse)))
		error_exit("get_intersect_sub_2\n");
	find_intersect(intersect, line, info->parse->objects);
	if (intersect->intersect == 0)
		return ;
	intersect_color(intersect, info->parse);
	copy_color(color, intersect->color);
	ft_free(intersect);
	ft_free(line);
}

t_intersect	*get_intersect(t_info *info, int *pixel, double *u, double *v)
{
	t_intersect	*intersect;
	int			color[3];
	double		*vector[2];

	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
	vector[0] = u;
	vector[1] = v;
	get_intersect_sub(color, pixel, info, vector);
	if (!(intersect = init_intersect(info->parse)))
		error_exit("get_intersect!\n");
	copy_color(intersect->color, color);
	return (intersect);
}
