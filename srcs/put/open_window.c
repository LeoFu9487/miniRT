#include "minirt.h"

int		close_program(void *param)
{
	/*t_info		*info;
	t_camera	*cam;
	int			ct;*/

	(void)param;
	printf("\nfinished!\n");
	exit(EXIT_SUCCESS);
	/*info = param;
	while (info->parse->camera)
	{
		cam = info->parse->camera->content;
		ct = -1;
		while (++ct < 8)
			mlx_destroy_image(info->mlx_ptr, cam->img_ptr[ct]);
		info->parse->camera = info->parse->camera->next;
	}
	if (info->win_ptr)
		mlx_destroy_window(info->mlx_ptr, info->win_ptr);
	free(info->mlx_ptr);
	ft_free_all();
	return (1);*/
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
	ft_putstr_fd("\rcurrent camera : ", 2);
	ft_putnbr_fd(camera->num, 2);
	if ((info->filter >> 3) & 1)
	{
		ft_putstr_fd(" wearing red-green glasses !                   ", 2);
		mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, camera->img_ptr[8], 0, 0);
	}
	else
	{
		if ((info->filter >> 2) & 1)
			ft_putstr_fd(" filter R : on ", 2);
		else
			ft_putstr_fd(" filter R : off", 2);
		if ((info->filter >> 1) & 1)
			ft_putstr_fd(" filter G : on ", 1);
		else
			ft_putstr_fd(" filter G : off", 1);
		if ((info->filter >> 0) & 1)
			ft_putstr_fd(" filter B : on ", 2);
		else
			ft_putstr_fd(" filter B : off", 2);
		mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, camera->img_ptr[info->filter], 0, 0);
	}
}

int		deal_key(int key, void *ptr)
{
	t_info		*info;
	t_camera	*camera;

	info = ptr;
	if (key == ESC)
		close_program(info);
	if (key == SPACE)
		change_camera(info);
	if (key == R)
		info->filter ^= 4;
	if (key == G)
		info->filter ^= 2;
	if (key == B)
		info->filter ^= 1;
	if (key == S)
		info->filter ^= 8;
	if (!(info->parse->cur_camera))
		return (0);
	camera = info->parse->cur_camera->content;
	ft_putstr_fd("\rcurrent camera : ", 2);
	ft_putnbr_fd(camera->num, 2);
	if ((info->filter >> 3) & 1)
	{
		ft_putstr_fd(" wearing red-green glasses !                   ", 2);
		mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, camera->img_ptr[8], 0, 0);
	}
	else
	{
		if ((info->filter >> 2) & 1)
			ft_putstr_fd(" filter R : on ", 2);
		else
			ft_putstr_fd(" filter R : off", 2);
		if ((info->filter >> 1) & 1)
			ft_putstr_fd(" filter G : on ", 1);
		else
			ft_putstr_fd(" filter G : off", 1);
		if ((info->filter >> 0) & 1)
			ft_putstr_fd(" filter B : on ", 2);
		else
			ft_putstr_fd(" filter B : off", 2);
		mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, camera->img_ptr[info->filter], 0, 0);
	}
	return (0);
}

t_info	*init_info(t_parse *parse, void *mlx_ptr, void *win_ptr)
{
	t_info	*info;

	if (!(info = ft_malloc(1, sizeof(t_info))))
		return (NULL);
	info->parse = parse;
	info->mlx_ptr = mlx_ptr;
	info->win_ptr = win_ptr;
	info->filter = 0;
	return (info);
}

void	open_window(t_parse *parse, t_info *info)
{
	void	*win_ptr;

	win_ptr = mlx_new_window(info->mlx_ptr, parse->rx, parse->ry, "miniRT");
	info->win_ptr = win_ptr;
	mlx_hook(win_ptr, 17, 131072, close_program, info);
	mlx_key_hook(win_ptr, deal_key, info);
	mlx_loop(info->mlx_ptr);
}
