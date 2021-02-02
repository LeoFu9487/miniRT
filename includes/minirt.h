/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:57:15 by yfu               #+#    #+#             */
/*   Updated: 2021/02/02 11:57:16 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include "../lib/libft/libft.h"
# ifdef LINUX
#  include "../lib/minilibx-linux/mlx.h"
#  define ESC 65307
# endif
# ifdef MACOS
#  include "../lib/minilibx_opengl_20191021/mlx.h"
#  define ESC 53
# endif

void	arg_error(int argc, char **argv);

#endif
