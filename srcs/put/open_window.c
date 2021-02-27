#include "minirt.h"

int		close_program(void *param)
{
	t_info		*info;
	t_camera	*cam;

	info = param;
	while (info->parse->camera)
	{
		cam = info->parse->camera->content;
		mlx_destroy_image(info->mlx_ptr, cam->img_ptr);
		info->parse->camera = info->parse->camera->next;
	}
	printf("\nprogram is closed!\n");
	ft_free_all();
	exit(EXIT_SUCCESS);
	return (1);
}

void	change_camera(t_info *info)
{
	t_parse		*parse;
	t_camera	*camera;

	parse = info->parse;
	if (parse->cur_camera == NULL || parse->cur_camera->next == NULL)
		parse->cur_camera = parse->camera;
	else
		parse->cur_camera = parse->cur_camera->next;
	camera = parse->cur_camera->content;
	ft_putstr_fd("\rcamera ", 2);
	ft_putnbr_fd(camera->num, 2);
	mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, camera->img_ptr, 0, 0);
}

int		deal_key(int key, void *info)
{
	if (key == ESC)
		close_program(info);
	if (key == SPACE)
		change_camera(info);
	return (0);
}

t_info	*init_info(t_parse *parse, void *mlx_ptr, void *win_ptr)
{
	t_info	*info;

	info = ft_malloc(1, sizeof(t_info));
	info->parse = parse;
	info->mlx_ptr = mlx_ptr;
	info->win_ptr = win_ptr;
	return (info);
}

void	open_window(t_parse *parse)
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		sizex;
	int		sizey;
	t_info	*info;

	mlx_ptr = mlx_init();
	mlx_get_screen_size(mlx_ptr, &sizex, &sizey);
	parse->rx = ft_min(parse->rx, sizex);
	parse->ry = ft_min(parse->ry, sizey);
	info = init_info(parse, mlx_ptr, (void*)NULL);
	load_images(info);
	ft_putendl_fd("finish loading", 2);
	win_ptr = mlx_new_window(mlx_ptr, parse->rx, parse->ry, "miniRT");
	info->win_ptr = win_ptr;
	ft_putendl_fd("current camera :", 2);
	mlx_hook(win_ptr, 17, 131072, close_program, info);
	mlx_key_hook(win_ptr, deal_key, info);
	mlx_loop(mlx_ptr);
}
