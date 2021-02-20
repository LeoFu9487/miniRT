#ifndef PUT_H
# define PUT_H

typedef struct	s_info
{
	t_parse	*parse;
	void	*mlx_ptr;
	void	*win_ptr;
}				t_info;

int				get_color(int *rgb);
void			put_all(t_info *info);
void			put_pixel(t_info *info, int	*pixel, double *u, double *v);
void			put_scene(t_parse *parse);
int				close_program(void *param);
void			change_camera(t_info *info);
int				deal_key(int key, void *parse);
void			open_window(t_parse *parse);
void			put_screen(t_info *info);
t_info			*init_info(t_parse *parse, void *mlx_ptr, void *win_ptr);

#endif
