/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 19:55:26 by yfu               #+#    #+#             */
/*   Updated: 2021/03/02 22:30:09 by yfu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUT_H
# define PUT_H
# define GLASSES_DISTANCE 40
# define WAVE_AMPLITUDE 10
# define WAVE_LAMBDA 10

typedef struct	s_info
{
	t_parse	*parse;
	void	*mlx_ptr;
	void	*win_ptr;
	int		filter;
}				t_info;

void			clean_screen(t_info *info);
int				get_color(int *rgb);
void			put_all(t_info *info);
void			put_pixel(t_info *info, int	*pixel, double *u, double *v);
void			put_scene(t_parse *parse);
int				close_program(void *param);
void			change_camera(t_info *info);
int				deal_key(int key, void *parse);
void			open_window(t_parse *parse, t_info *info);
void			put_screen(t_info *info);
void			load_images(t_info *info);
t_info			*init_info(t_parse *parse, void *mlx_ptr, void *win_ptr);

#endif
