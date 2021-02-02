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

typedef struct	s_parse
{
	int		Rx;
	int		Ry;
	double	Aratio;
	int		Acolor[3];
	t_list	*camera;
	t_list	*light;
	t_list	*obj;
}				t_parse;

typedef enum	e_parse_type
{
	R = 0,
	A,
	c,
	l,
	sp,
	pl,
	sq,
	cy,
	tr
}				t_parse_type;

void	arg_error(int argc, char **argv);
int		file_error(char **argv);
void	parse_scene(int fd, t_parse *parse);
void	parse_r(t_parse *parse, char *str);
void	parse_a(t_parse *parse, char *str);
void	parse_c(t_parse *parse, char *str);
void	parse_l(t_parse *parse, char *str);
void	parse_sp(t_parse *parse, char *str);
void	parse_pl(t_parse *parse, char *str);
void	parse_sq(t_parse *parse, char *str);
void	parse_cy(t_parse *parse, char *str);
void	parse_tr(t_parse *parse, char *str);
t_parse	*init_parse(void);

#endif
