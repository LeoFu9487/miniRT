/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:57:24 by yfu               #+#    #+#             */
/*   Updated: 2021/02/02 12:00:49 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	arg_error(int argc, char **argv)
{
	if (argc < 2 || argc > 3)
		printf("ERROR : Wrong amounts of arguments.\n");
	else if (ft_strlen(argv[1]) < 3 ||
			ft_strncmp(".rt", ft_substr(argv[1], ft_strlen(argv[1]) - 3, 3), 3))
		printf("ERROR : The second argument should be in type *.rt\n");
	else if (argc == 3 && ft_strncmp(argv[2], "--save", 7))
		printf("ERROR : The third argument should be --save or nothing\n");
	else
		return ;
	printf("Usage 1 : %s <scene.rt>\n", argv[0]);
	printf("Usage 2 : %s <scene.rt> --save\n", argv[0]);
	exit(EXIT_FAILURE);
}

int		file_error(char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		printf("ERROR : Can't open file %s \n", argv[1]);
		exit(EXIT_FAILURE);
	}
	return (fd);
}
