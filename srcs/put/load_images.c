#include "minirt.h"

void	load_images(t_info *info)
{
	t_camera	*camera;

	info->parse->cur_camera = info->parse->camera;
	while (info->parse->cur_camera)
	{
		camera = info->parse->cur_camera->content;
		camera->img_ptr[0] = mlx_new_image(info->mlx_ptr, info->parse->rx, info->parse->ry);
		camera->pixel[0] = (int*)mlx_get_data_addr(camera->img_ptr[0], camera->bits_per_pixel[0], camera->size_line[0], camera->endian[0]);
		camera->img_ptr[1] = mlx_new_image(info->mlx_ptr, info->parse->rx, info->parse->ry);
		camera->pixel[1] = (int*)mlx_get_data_addr(camera->img_ptr[1], camera->bits_per_pixel[1], camera->size_line[1], camera->endian[1]);
		ft_putstr_fd("loading camera : ", 2);
		ft_putnbr_fd(camera->num,  2);
		ft_putendl_fd("", 2);
		put_screen(info);;
		info->parse->cur_camera = info->parse->cur_camera->next;
	}
}
