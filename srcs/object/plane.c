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

static void	plane_coef(double *coef, t_plane *plane)
{
	coef[0] = plane->orientation[0];
	coef[1] = plane->orientation[1];
	coef[2] = plane->orientation[2];
	coef[3] = -1.0 * (plane->coordinate[0] * coef[0] + plane->coordinate[1] * coef[1] + plane->coordinate[2] * coef[2]);
}

void		intersect_pl(t_intersect *is, t_line *l, void *ptr, int num)
{
	t_plane	*plane;
	double	ans;
	double	coef[4];

	if (!have_intersection_pl(l, ptr))
		return ;
	plane = ptr;
	plane_coef(coef, plane);
	ans = linear_equation(coef, l);
	if (is->intersect == 0 || ans < is->dist)
	{
		is->dist = ans;
		is->intersect = 1;
		is->coordinate[0] = l->x[0] * is->dist + l->x[1];
		is->coordinate[1] = l->y[0] * is->dist + l->y[1];
		is->coordinate[2] = l->z[0] * is->dist + l->z[1];
		is->obj_num = num;
	}
}

/*
typedef struct	s_intersect
{
	int		intersect;
	double	coordinate[3];
	int		color[3];
	double	dist;
	int		obj_num;
}				t_intersect;
*/

int				have_intersection_pl(t_line *l, void *ptr)
{
	t_plane	*plane;
	double	res;
	double	vector[3];
	double	coef[4];

	plane = ptr;
	vector[0] = l->x[0];
	vector[1] = l->y[0];
	vector[2] = l->z[0];
	res = cos_vector(plane->orientation, vector);
	if (res < 1e-6 && res > -1e-6)
		return (0);
	plane_coef(coef, plane);
	res = linear_equation(coef, l);
	if (res < 1.0 - 1e-6 && res > 1e-6)
		return (1);
	return (0);
}

double			*normal_vector_pl(double *point, void *ptr)
{
	double	*ans;
	t_plane	*plane;

	if (!(ans = ft_malloc(3, sizeof(double))))
		error_exit("normal_vector_pl\n");
	plane = ptr;
	ans[0] = plane->orientation[0];
	ans[1] = plane->orientation[1];
	ans[2] = plane->orientation[2];
	(void)point;
	return (ans);
}
