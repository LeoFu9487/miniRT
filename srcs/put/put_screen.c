/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_screen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 20:14:50 by yfu               #+#    #+#             */
/*   Updated: 2021/03/02 22:30:36 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	put_all_sub(t_info *info, int *ct, double *u, double *base_v)
{
	ft_putstr_fd("\rloading ... ", 2);
	ft_putnbr_fd(ct[0] * 100 / (info->parse->rx + GLASSES_DISTANCE), 2);
	ft_putstr_fd(" %", 2);
	ct[1] = -1 - WAVE_AMPLITUDE;
	while (++ct[1] < info->parse->ry + WAVE_AMPLITUDE)
		put_pixel(info, ct, u, base_v);
}

void		put_all(t_info *info)
{
	int			ct[2];
	t_camera	*camera;
	double		base_v[3];
	double		*u;

	camera = info->parse->cur_camera->content;
	base_v[0] = 0.0;
	if (camera->orientation[0] == 0.0 && camera->orientation[1] == 0.0)
		base_v[1] = 1.0;
	else
		base_v[1] = 0.0;
	base_v[2] = 1.0 - base_v[1];
	modify_length(camera->orientation, camera->distance_to_screen);
	u = cross(base_v, camera->orientation);
	modify_length(u, 1.0);
	ct[0] = -1;
	while (++ct[0] < info->parse->rx + GLASSES_DISTANCE)
		put_all_sub(info, ct, u, base_v);
	ft_putendl_fd("\rloading ... 100 %", 2);
	ft_free(u);
}

static void	put_pixel_sub_sub(int use[2][3], t_info *info, int *pixel)
{
	t_camera	*camera;

	camera = info->parse->cur_camera->content;
	if (pixel[0] >= 0 && pixel[0] < info->parse->rx &&
	pixel[1] >= 0 && pixel[1] < info->parse->ry)
	{
		camera->pixel[16][pixel[0] + pixel[1] * info->parse->rx] =
		camera->pixel[5][pixel[0] + pixel[1] * info->parse->rx];
		camera->pixel[16][pixel[0] + pixel[1] * info->parse->rx] +=
		camera->pixel[6][pixel[0] + pixel[1] * info->parse->rx] / 2;
	}
	if (info->parse->rx >= GLASSES_DISTANCE && pixel[0] >= GLASSES_DISTANCE
	&& pixel[1] >= 0 && pixel[1] < info->parse->ry)
	{
		camera->pixel[16][pixel[0] + pixel[1] * info->parse->rx -
		GLASSES_DISTANCE] += get_color(use[0]);
		camera->pixel[16][pixel[0] + pixel[1] * info->parse->rx -
		GLASSES_DISTANCE] += get_color(use[1]) / 2;
	}
}

static void	put_pixel_sub(int use[2][3], t_intersect *intersect,
t_info *info, int *pixel)
{
	int				y;
	int				ct;
	t_camera		*camera;
	int				color[3];

	ct = 7;
	camera = info->parse->cur_camera->content;
	y = pixel[1] + (int)((double)WAVE_AMPLITUDE *
	sin((double)pixel[0] / (double)WAVE_LAMBDA));
	if (pixel[0] >= 0 && pixel[0] < info->parse->rx &&
	y >= 0 && y < info->parse->ry)
		while (++ct < 16)
		{
			color[0] = (((ct >> 2) & 1) ^ 1) * intersect->color[0];
			color[1] = (((ct >> 1) & 1) ^ 1) * intersect->color[1];
			color[2] = (((ct >> 0) & 1) ^ 1) * intersect->color[2];
			camera->pixel[ct][pixel[0] + y * info->parse->rx] =
			get_color(color);
		}
	put_pixel_sub_sub(use, info, pixel);
}

void		put_pixel(t_info *info, int *pixel, double *u, double *v)
{
	t_intersect	*intersect;
	t_camera	*camera;
	int			color[3];
	int			use[2][3];
	int			ct;

	if (!(intersect = get_intersect(info, pixel, u, v)))
		error_exit("put_pixel\n");
	ct = -1;
	camera = info->parse->cur_camera->content;
	while (++ct < 8)
	{
		color[0] = (((ct >> 2) & 1) ^ 1) * intersect->color[0];
		color[1] = (((ct >> 1) & 1) ^ 1) * intersect->color[1];
		color[2] = (((ct >> 0) & 1) ^ 1) * intersect->color[2];
		if (pixel[0] >= 0 && pixel[0] < info->parse->rx &&
		pixel[1] >= 0 && pixel[1] < info->parse->ry)
			camera->pixel[ct][pixel[0] + pixel[1] * info->parse->rx] =
			get_color(color);
		if (ct == 3 || ct == 6)
			copy_color(use[(ct - 3) / 3], color);
	}
	put_pixel_sub(use, intersect, info, pixel);
	ft_free(intersect);
}
