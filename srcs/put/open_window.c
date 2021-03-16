/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 01:31:41 by yfu               #+#    #+#             */
/*   Updated: 2021/03/03 01:58:42 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		close_program(void *param)
{
	(void)param;
	printf("\nfinished!\n");
	exit(EXIT_SUCCESS);
	return (1);
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
