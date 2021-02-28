#include "bonus.h"

t_info	*g_info;

void	load_images_bonus(t_info *info)
{
	t_camera	*camera;
	pthread_t	thread[1000];
	int			ct[2];

	info->parse->cur_camera = info->parse->camera;
	ct[0] = 0;
	g_info = info;
	while (info->parse->cur_camera)
	{
		if (ct[0] >= 1000)
			error_exit("Too many cameras !\n");
		camera = info->parse->cur_camera->content;
		camera->img_ptr = mlx_new_image(info->mlx_ptr, info->parse->rx, info->parse->ry);
		camera->pixel = (int*)mlx_get_data_addr(camera->img_ptr, camera->bits_per_pixel, camera->size_line, camera->endian);
		ft_putstr_fd("loading camera : ", 2);
		ft_putnbr_fd(camera->num,  2);
		ft_putendl_fd("", 2);
		pthread_create(&(thread[ct[0]++]), NULL, put_screen_bonus, camera);
		info->parse->cur_camera = info->parse->cur_camera->next;
	}
	ct[1] = -1;
	while (++ct[1] < ct[0])
		pthread_join(thread[ct[1]], NULL);
}

void	put_all_bonus(t_camera *camera)
{
	int			ct[2];
	double		base_v[3];
	double		*u;

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
	while (++ct[0] < g_info->parse->rx)
	{
		ft_putstr_fd("\rloading ... ", 2);
		ft_putnbr_fd(ct[0] * 100 / g_info->parse->rx, 2);
		ft_putstr_fd(" %", 2);
		ct[1] = -1;
		while (++ct[1] < g_info->parse->ry)
			put_pixel_bonus(camera, ct, u, base_v);
	}
	ft_putendl_fd("\rloading ... 100 %", 2);
	ft_free(u);
}

void	put_pixel_bonus(t_camera *camera, int *pixel, double *u, double *v)
{
	double		position[2];
	t_line		*line;
	t_intersect	*intersect;

	position[0] = ((double)pixel[0]) - ((double)g_info->parse->rx) / 2.0;
	position[1] = ((double)pixel[1]) - ((double)g_info->parse->ry) / 2.0;
	if (!(line = new_line(camera, u, v, position)) || !(intersect = init_intersect(g_info->parse)))
		return ;
	find_intersect(intersect, line, g_info->parse->objects);
	if (intersect->intersect == 0)
		return ;
	intersect_color_bonus(intersect, g_info->parse, camera);
	camera->pixel[pixel[0] + pixel[1] * g_info->parse->rx] = get_color(intersect->color);
	ft_free(line);
	ft_free(intersect);
}

void	*put_screen_bonus(void *ptr)
{
	t_camera	*camera;

	camera = (t_camera*)ptr;
	if (!camera)
		error_exit("put_screen_bonus\n");
	if (camera->vof > 170.0)
		camera->vof = 170.0;
	if (camera->distance_to_screen == 0.0)
		camera->distance_to_screen =
		((double)g_info->parse->rx) / 2.0 / tan(camera->vof / 2.0 * M_PI / 180.0);
	put_all_bonus(camera);
	return (NULL);
}
