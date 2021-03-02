/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:57:15 by yfu               #+#    #+#             */
/*   Updated: 2021/03/02 19:58:54 by yfu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include "../lib/libft/libft.h"
# include "parse.h"
# include "put.h"
# include "math2.h"
# include "bmp.h"
# ifdef LINUX
#  include "../lib/minilibx-linux/mlx.h"
#  include "../lib/minilibx-linux/mlx_int.h"
#  define OS 0
#  define ESC 65307
#  define SPACE 32
#  define R 114
#  define G 103
#  define B 98
#  define S 115
#  define W 119
# endif
# ifdef MACOS
#  include "../lib/minilibx_opengl_20191021/mlx.h"
#  define OS 1
#  define ESC 53
# endif
# ifndef DEBUG
#  define DEBUG 0
# endif

void	arg_error(int argc, char **argv);
int		file_error(char **argv);
void	error_exit(const char *str);
t_info	*get_images(t_parse *parse);

#endif
