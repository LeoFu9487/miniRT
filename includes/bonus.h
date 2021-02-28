#ifndef BONUS_H
# define BONUS_H
# include <pthread.h>
# include "minirt.h"

typedef struct	s_bonus
{
	int		x;
	double	*u;
	double	*v;
}				t_bonus;

void	load_images_bonus(t_info *info);
void	put_all_bonus(t_camera *camera);
void	put_pixel_bonus(t_camera *camera, int *pixel, double *u, double *v);
void	*put_screen_bonus(void *ptr);
void	*render_thread(void *bonus);
void	intersect_color_bonus(t_intersect *it, t_parse *parse, t_camera *camera);

#endif