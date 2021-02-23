#include "minirt.h"

int		close_program(void *param)
{
	(void)param;
	printf("program is closed!\n");
	ft_free_all();
	exit(EXIT_SUCCESS);
	return (1);
}

void	change_camera(t_info *info)
{
	t_parse	*parse;

	clean_screen(info);
	parse = info->parse;
	if (parse->cur_camera == NULL || parse->cur_camera->next == NULL)
		parse->cur_camera = parse->camera;
	else
		parse->cur_camera = parse->cur_camera->next;
	put_screen(info);
}

int		deal_key(int key, void *info)
{
	if (key == ESC)
		close_program((void*)0);
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
	win_ptr = mlx_new_window(mlx_ptr, parse->rx, parse->ry, "minirt");
	info = init_info(parse, mlx_ptr, win_ptr);
	mlx_hook(win_ptr, 17, 131072, close_program, (void*)0);
	mlx_key_hook(win_ptr, deal_key, info);
	mlx_loop(mlx_ptr);
}
