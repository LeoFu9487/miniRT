/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:57:15 by yfu               #+#    #+#             */
/*   Updated: 2021/03/09 10:38:52 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include "libft.h"
# include "parse.h"
# include "put.h"
# include "math2.h"
# include "bmp.h"
# ifdef LINUX
#  include "mlx.h"
#  include "mlx_int.h"
#  define OS 0
#  define ESC 65307
#  define SPACE 32
#  define _R 114
#  define G 103
#  define B 98
#  define S 115
#  define W 119
# endif
# ifdef MACOS
#  include "mlx.h"
#  define OS 1
#  define ESC 53
#  define SPACE 49
#  define _R 15
#  define G 5
#  define B 11
#  define S 1
#  define W 13
#  define OS 1
#  define ESC 53
# endif
# ifndef DEBUG
#  define DEBUG 0
# endif

void	arg_error(int argc, char **argv);
int		file_error(char **argv);
void	error_exit(const char *str);
void	mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey);
t_info	*get_images(t_parse *parse);

#endif
