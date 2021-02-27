#include "minirt.h"

void	load_images(t_info *info)
{
	t_camera	*camera;

	info->parse->cur_camera = info->parse->camera;
	while (info->parse->cur_camera)
	{
		camera = info->parse->cur_camera->content;
		camera->img_ptr = mlx_new_image(info->mlx_ptr, info->parse->rx, info->parse->ry);
		camera->pixel = (int*)mlx_get_data_addr(camera->img_ptr, camera->bits_per_pixel, camera->size_line, camera->endian);
		ft_putstr_fd("loading camera : ", 2);
		ft_putnbr_fd(camera->num,  2);
		ft_putendl_fd("", 2);
		put_screen(info);
		info->parse->cur_camera = info->parse->cur_camera->next;
	}
}
