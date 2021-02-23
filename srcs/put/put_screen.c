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
	double		*v;

	camera = info->parse->cur_camera->content;
	base_v[0] = 0.0;
	if (camera->orientation[0] == 0.0 && camera->orientation[1] == 0.0)
		base_v[1] = 1.0;
	else
		base_v[1] = 0.0;
	base_v[2] = 1.0 - base_v[1];
	u = cross(base_v, camera->orientation);
	v = cross(u, camera->orientation);
	ct[0] = -1;
	while (++ct[0] < info->parse->rx)
	{
		ct[1] = -1;
		while (++ct[1] < info->parse->ry)
			put_pixel(info, ct, u, v);
	}
	ft_free(u);
	ft_free(v);
}

void	put_pixel(t_info *info, int *pixel, double *u, double *v)
{
	int			position[2];
	t_line		*line;
	t_intersect	*intersect;

	position[0] = pixel[0] - info->parse->rx / 2;
	position[1] = pixel[1] - info->parse->ry / 2;
	if (!(line = new_line(info->parse->cur_camera->content, u, v, position)) || !(intersect = init_intersect()))
		return ;
	find_intersect(intersect, line, info->parse->objects);
	if (intersect->intersect == 0)
		return ;
	intersect_color(intersect, info->parse);
	mlx_pixel_put(info->mlx_ptr, info->win_ptr, pixel[0], pixel[1], get_color(intersect->color));
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
