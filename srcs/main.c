/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:57:30 by yfu               #+#    #+#             */
/*   Updated: 2021/02/02 11:57:33 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		main(int argc, char **argv)
{
	int			fd;
	t_parse		*parse;

	arg_error(argc, argv);
	fd = file_error(argv);
	if (!(parse = init_parse()))
		error_exit("ERROR_IN_MAIN\n");
	parse_scene(fd, parse);
	ft_free_all();
}
