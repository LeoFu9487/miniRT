#include "minirt.h"

t_square	*init_square(void)
{
	t_square	*square;
	int			ct;

	if (!(square = ft_malloc(1, sizeof(t_square))))
	{
		printf("ERROR_IN_INIT_SQUARE\n");
		return (NULL);
	}
	ct = -1;
	while (++ct < 3)
		square->coordinate[ct] = 0.0;
	ct = -1;
	while (++ct < 3)
		square->orientation[ct] = 0.0;
	square->side_size = 0.0;
	ct = -1;
	while (++ct < 3)
		square->color[ct] = 0;
	return (square);
}

void		intersect_sq(t_intersect *is, t_line *l, void *ptr, int num)
{
	(void)num;
	(void)is;
	(void)l;
	(void)ptr;
	/*
	 * ptr is already t_cyliner * or t_triagle *...etc.
	 * */
}

int				have_intersection_sq(t_line *l, void *ptr)
{
		(void)l;(void)ptr;

	return (0);
}

double			*normal_vector_sq(double *point, void *ptr)
{
	double		*ans;
    t_square	*plane;

    if (!(ans = ft_malloc(3, sizeof(double))))
            error_exit("normal_vector_pl\n");
	plane = ptr;
    ans[0] = plane->orientation[0];
    ans[1] = plane->orientation[1];
    ans[2] = plane->orientation[2];
    (void)point;
    return (ans);
}
