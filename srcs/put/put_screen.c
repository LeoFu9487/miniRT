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
	while (++ct[0] < info->parse->rx + GLASSES_DISTANCE)
	{
		ft_putstr_fd("\rloading ... ", 2);
		ft_putnbr_fd(ct[0] * 100 / (info->parse->rx + GLASSES_DISTANCE), 2);
		ft_putstr_fd(" %", 2);
		ct[1] = -1 - WAVE_AMPLITUDE;
		while (++ct[1] < info->parse->ry + WAVE_AMPLITUDE)
			put_pixel(info, ct, u, base_v);
	}
	ft_putendl_fd("\rloading ... 100 %", 2);
	ft_free(u);
}

void	put_pixel(t_info *info, int *pixel, double *u, double *v)
{
	double		position[2];
	t_line		*line;
	t_intersect	*intersect;
	t_camera	*camera;
	int			color[3];
	int			use[2][3];
	int			ct;
	int			y;

	position[0] = ((double)pixel[0]) - ((double)info->parse->rx) / 2.0;
	position[1] = ((double)pixel[1]) - ((double)info->parse->ry) / 2.0;
	if (!(line = new_line(info->parse->cur_camera->content, u, v, position)) || !(intersect = init_intersect(info->parse)))
		return ;
	find_intersect(intersect, line, info->parse->objects);
	if (intersect->intersect == 0)
		return ;
	intersect_color(intersect, info->parse);
	camera = info->parse->cur_camera->content;
	ct = -1;
	while (++ct < 8)
	{
		color[0] = (((ct >> 2) & 1) ^ 1) * intersect->color[0];
		color[1] = (((ct >> 1) & 1) ^ 1) * intersect->color[1];
		color[2] = (((ct >> 0) & 1) ^ 1) * intersect->color[2];
		if (pixel[0] >= 0 && pixel[0] < info->parse->rx && pixel[1] >= 0 && pixel[1] < info->parse->ry)
			camera->pixel[ct][pixel[0] + pixel[1] * info->parse->rx] = get_color(color);
		if (ct == 3)
			copy_color(use[0], color);
		if (ct == 6)
			copy_color(use[1], color);
	}
	--ct;
	y = pixel[1] + (int)((double)WAVE_AMPLITUDE * sin((double)pixel[0] / (double)WAVE_LAMBDA));
	if (pixel[0] >= 0 && pixel[0] < info->parse->rx && y >= 0 && y < info->parse->ry)
		while (++ct < 16)
		{
			color[0] = (((ct >> 2) & 1) ^ 1) * intersect->color[0];
			color[1] = (((ct >> 1) & 1) ^ 1) * intersect->color[1];
			color[2] = (((ct >> 0) & 1) ^ 1) * intersect->color[2];
			camera->pixel[ct][pixel[0] + y * info->parse->rx] = get_color(color);
		}
	if (pixel[0] >= 0 && pixel[0] < info->parse->rx && pixel[1] >= 0 && pixel[1] < info->parse->ry)
	{
		camera->pixel[16][pixel[0] + pixel[1] * info->parse->rx] = camera->pixel[5][pixel[0] + pixel[1] * info->parse->rx];
		camera->pixel[16][pixel[0] + pixel[1] * info->parse->rx] += camera->pixel[6][pixel[0] + pixel[1] * info->parse->rx] * 0.5;
	}
	if (info->parse->rx >= GLASSES_DISTANCE && pixel[0] >= GLASSES_DISTANCE && pixel[1] >= 0 && pixel[1] < info->parse->ry)
	{
		camera->pixel[16][pixel[0] + pixel[1] * info->parse->rx - GLASSES_DISTANCE] += get_color(use[0]);
		camera->pixel[16][pixel[0] + pixel[1] * info->parse->rx - GLASSES_DISTANCE] += get_color(use[1]) * 0.5;
	}
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
