#include "minirt.h"

t_line		*new_line(t_camera *camera, double *u, double *v, int *position)
{
	t_line	*line;

	if (!(line = ft_malloc(1, sizeof(t_line))))
		return (NULL);
	line->x[1] = camera->coordinate[0];
	line->y[1] = camera->coordinate[1];
	line->z[1] = camera->coordinate[2];
	line->x[0] = camera->orientation[0] + position[0] * u[0] + position[1] * v[0];
	line->y[0] = camera->orientation[1] + position[0] * u[1] + position[1] * v[1];
	line->z[0] = camera->orientation[2] + position[0] * u[2] + position[1] * v[2];
	return (line);
}

t_intersect	*init_intersect(void)
{
	t_intersect	*intersect;

	if (!(intersect = ft_malloc(1, sizeof(t_intersect))))
		return (NULL);
	intersect->intersect = 0;
	return (intersect);
}

void		find_intersect(t_intersect *is, t_line *l, t_list *obj)
{
	/*
	not done yet
	*/
}
