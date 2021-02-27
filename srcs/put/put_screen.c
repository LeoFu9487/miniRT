#include "minirt.h"

void	clean_screen(t_info *info)
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

void	put_all(t_info *info)
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
	while (++ct[0] < info->parse->rx)
	{
		ct[1] = -1;
		while (++ct[1] < info->parse->ry)
			put_pixel(info, ct, u, base_v);
	}
	ft_free(u);
}

void	put_pixel(t_info *info, int *pixel, double *u, double *v)
{
	double		position[2];
	t_line		*line;
	t_intersect	*intersect;
	t_camera	*camera;

	position[0] = ((double)pixel[0]) - ((double)info->parse->rx) / 2.0;
	position[1] = ((double)pixel[1]) - ((double)info->parse->ry) / 2.0;
	if (!(line = new_line(info->parse->cur_camera->content, u, v, position)) || !(intersect = init_intersect(info->parse)))
		return ;
	find_intersect(intersect, line, info->parse->objects);
	if (intersect->intersect == 0)
		return ;
	intersect_color(intersect, info->parse);
	camera = info->parse->cur_camera->content;
	camera->pixel[pixel[0] + pixel[1] * info->parse->rx] = get_color(intersect->color);
	//mlx_pixel_put(info->mlx_ptr, info->win_ptr, pixel[0], pixel[1], get_color(intersect->color));
	ft_free(line);
	ft_free(intersect);
}

void	put_screen(t_info *info)
{
	t_camera	*camera;

	if (info->parse->cur_camera == NULL)
		error_exit("Camera not found !! cannot put_screen\n");
	camera = (t_camera*)(info->parse->cur_camera->content);
	if (camera->vof > 170.0)
		camera->vof = 170.0;
	if (camera->distance_to_screen == 0.0)
		camera->distance_to_screen =
		((double)info->parse->rx) / 2.0 / tan(camera->vof / 2.0 * M_PI / 180.0);
	put_all(info);
}
