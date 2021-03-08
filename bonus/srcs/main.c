/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:57:30 by yfu               #+#    #+#             */
/*   Updated: 2021/03/08 14:40:30 by yfu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_info	*get_images(t_parse *parse)
{
	void	*mlx_ptr;
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
	return (info);
}

int		main(int argc, char **argv)
{
	int			fd;
	t_parse		*parse;
	t_info		*info;

	arg_error(argc, argv);
	fd = file_error(argv);
	if (!(parse = init_parse()))
		error_exit("ERROR_IN_MAIN\n");
	parse_scene(fd, parse);
	info = get_images(parse);
	if (argc == 2)
	{
		ft_putendl_fd("press space to start and change camera", 2);
		ft_putendl_fd("press r,g,b for RGB filter", 2);
		ft_putendl_fd("press w for wave effect", 2);
		ft_putendl_fd("press s for stereocopy", 2);
		ft_putendl_fd("press ESC to close the program", 2);
		open_window(parse, info);
	}
	else
		do_bmp(info, argv);
	return (0);
}
