#include "minirt.h"

t_cube	*init_cube(void)
{
	t_cube	*cube;
	int		ct;

	if (!(cube = ft_malloc(1, sizeof(t_cube))))
		error_exit("INIT_CUBE\n");
	cube->side_size = -1.0;
	ct = -1;
	while (++ct < 6)
		cube->square[ct] = NULL;
	return (cube);
}

void	compose_cube(t_cube *cube)
{
	int			ct;
	int			n;
	t_square	*square;
	double		*vector[3];
	double		*point[2];
	double		*temp;

	ct = -1;
	if (!(point[0] = ft_malloc(3, sizeof(double))))
			error_exit("compose_cube\n");
	if (!(point[1] = ft_malloc(3, sizeof(double))))
			error_exit("compose_cube\n");
	while (++ct < 3)
	{
		if (!(vector[ct] = ft_malloc(3, sizeof(double))))
			error_exit("compose_cube\n");
		vector[ct][0] = 0.0;
		vector[ct][1] = 0.0;
		vector[ct][2] = 0.0;
		vector[ct][ct] = cube->side_size;
		point[0][ct] = cube->coordinate[ct] - cube->side_size / 2.0;
		point[1][ct] = cube->coordinate[ct] + cube->side_size / 2.0;
	}
	ct = -1;
	while (++ct < 6)
	{
		if (!(cube->square[ct] = init_square()))
			error_exit("compose_cube\n");
		square = cube->square[ct];
		square->color[0] = cube->color[0];
		square->color[1] = cube->color[1];
		square->color[2] = cube->color[2];
		square->side_size = cube->side_size;
		copy_vector(square->start_point, point[ct % 2]);
		copy_vector(square->orientation, vector[ct / 2]);
		n = 0;
		if (ct / 2 != 0)
			square->vector[n++] = make_point(vector[0][0], vector[0][1], vector[0][2]);
		if (ct / 2 != 1)
			square->vector[n++] = make_point(vector[1][0], vector[1][1], vector[1][2]);
		if (ct / 2 != 2)
			square->vector[n++] = make_point(vector[2][0], vector[2][1], vector[2][2]);
		if (ct % 2)
		{
			modify_length(square->vector[0], -1 * cube->side_size);
			modify_length(square->vector[1], -1 * cube->side_size);
		}
		modify_length(square->orientation, cube->side_size / 2.0);
		if (ct % 2)
			modify_length(square->orientation, -0.5 * cube->side_size);
		temp = two_points_vector(square->orientation, cube->coordinate);
		copy_vector(square->coordinate, temp);
		modify_length(square->orientation, -0.5 * cube->side_size);
		ft_free(temp);
	}
	ft_free(point[0]);
	ft_free(point[1]);
	ft_free(vector[0]);
	ft_free(vector[1]);
	ft_free(vector[2]);
}

int				have_intersection_cu(t_line *l, void *ptr)
{
	int		ct;
	t_cube	*cube;

	ct = -1;
	cube = ptr;
	while (++ct < 6)
		if (have_intersection_sq(l, cube->square[ct]))
			return (1);
	return (0);
}

void			intersect_cu(t_intersect *is, t_line *l, void *ptr, int num)
{
	t_cube	*cube;
	int		ct;

	cube = ptr;
	ct = -1;
	while (++ct < 6)
		intersect_sq(is, l, cube->square[ct], num);
}

double			*normal_vector_cu(double *point, void *ptr)
{
	double	*ans;
	t_cube	*cube;
	int		ct;

	cube = ptr;
	if (!(ans = ft_malloc(3, sizeof(double))))
		error_exit("normal_vector_cu\n");
	ct = -1;
	while (++ct < 6)
	{
		if (double_abs(dot(cube->square[ct]->coordinate, cube->square[ct]->orientation) - dot(cube->square[ct]->orientation, point)) < 1e-6)
			copy_vector(ans, cube->square[ct]->orientation);
	}
	return (ans);
}
