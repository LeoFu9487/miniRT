#include "minirt.h"

t_triangle		*init_triangle(void)
{
	t_triangle	*triangle;
	int			ct[2];

	if (!(triangle = ft_malloc(1, sizeof(t_triangle))))
	{
		printf("Error\nERROR_IN_INIT_TRIANGLE\n");
		return (NULL);
	}
	ct[0] = -1;
	while (++ct[0] < 3)
	{
		ct[1] = -1;
		while (++ct[1] < 3)
			triangle->point[ct[0]][ct[1]] = 0.0;
	}
	ct[0] = -1;
	while (++ct[0] < 3)
		triangle->color[ct[0]] = 0;
	return (triangle);
}

void			intersect_tr(t_intersect *is, t_line *l, void *ptr, int num)
{
	(void)num;
	(void)is;
	(void)l;
	(void)ptr;
	/*
	 * ptr is already t_cyliner * or t_triagle *...etc.
	 * */
}

int				have_intersection_tr(t_line *l, void *ptr)
{	(void)l;(void)ptr;

	return (0);
}

double			*normal_vector_tr(double *point, void *ptr)
{
	(void)point;
	(void)ptr;
	return (NULL);
}
