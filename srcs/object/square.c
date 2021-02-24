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
	ct = -1;
	while (++ct < 3)
		square->start_point[ct] = 0.0;
	return (square);
}

static void	square_coef(double *coef, t_square *square)
{
	coef[0] = square->orientation[0];
	coef[1] = square->orientation[1];
	coef[2] = square->orientation[2];
	coef[3] = -1.0 * (square->coordinate[0] * coef[0] + square->coordinate[1] * coef[1] + square->coordinate[2] * coef[2]);
}

static int	in_square(t_line *line, t_square *square, double t)
{
	double	point[3];
	double	*v;
	double	ans[2];

	point[0] = line->x[0] * t + line->x[1];
	point[1] = line->y[0] * t + line->y[1];
	point[2] = line->z[0] * t + line->z[1];
	v = two_points_vector(square->start_point, point);
	linear_equations(square->vector[0], square->vector[1], v, ans);
	ft_free(v);
	if (ans[0] < 1.0 - 1e-6 && ans[0] > 1e-6 && ans[1] < 1.0 - 1e-6 && ans[1] > 1e-6)
		return (1);
	return (0);
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
	t_square	*square;
	double		coef[4];
	double		res;
	double		vector[3];

	square = ptr;
	vector[0] = l->x[0];
	vector[1] = l->y[0];
	vector[2] = l->z[0];
	res = cos_vector(square->orientation, vector);
	if (res < 1e-6 && res > -1e-6)
		return (0);
	square_coef(coef, square);
	res = linear_equation(coef, l);
	if (res > 1.0 - 1e-6 || res < 1e-6 || !(in_square(l, square, res)))
		return (0);
	return (1);
}

double			*normal_vector_sq(double *point, void *ptr)
{
	double		*ans;
    t_square	*square;

    if (!(ans = ft_malloc(3, sizeof(double))))
            error_exit("normal_vector_sq\n");
	square = ptr;
    ans[0] = square->orientation[0];
    ans[1] = square->orientation[1];
    ans[2] = square->orientation[2];
    (void)point;
    return (ans);
}
