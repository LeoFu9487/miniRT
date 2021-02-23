#include "minirt.h"

t_plane		*init_plane(void)
{
	t_plane	*plane;
	int		ct;

	if (!(plane = ft_malloc(1, sizeof(t_plane))))
	{
		printf("ERROR_IN_INIT_PLANE\n");
		return (NULL);
	}
	ct = -1;
	while (++ct < 3)
		plane->coordinate[3] = 0.0;
	ct = -1;
	while (++ct < 3)
		plane->orientation[3] = 0.0;
	ct = -1;
	while (++ct < 3)
		plane->color[3] = 0;
	return (plane);
}

void		intersect_pl(t_intersect *is, t_line *l, void *ptr, int num)
{
	(void)num;
	(void)is;
	(void)l;
	(void)ptr;
	/*
	 * ptr is already t_cyliner * or t_triagle *...etc.
	 * */
}

int				have_intersection_pl(t_line *l, void *ptr)
{
	(void)l;(void)ptr;
	return (0);
}

double			*normal_vector_pl(double *point, void *ptr)
{
	(void)point;
	(void)ptr;
	return (NULL);
}
