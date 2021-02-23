#include "minirt.h"

t_sphere	*init_sphere(void)
{
	int			cnt;
	t_sphere	*sphere;

	if (!(sphere = ft_malloc(1, sizeof(t_sphere))))
	{
		printf("ERROR_IN_INIT_SPHERE\n");
		return (NULL);
	}
	cnt = -1;
	while (++cnt < 3)
		sphere->coordinate[cnt] = 0.0;
	sphere->diameter = 0.0;
	cnt = -1;
	while (++cnt < 3)
		sphere->color[cnt] = 0;
	return (sphere);
}

void		intersect_sp(t_intersect *is, t_line *l, void *ptr)
{
	t_sphere	*sphere;
	double		answer[2];
	double		coef[3];
	int			ct;

	sphere = (t_sphere*)ptr;
	coef[0] = l->x[0] * l->x[0] + l->y[0] * l->y[0] + l->z[0] * l->z[0];
	coef[1] = 2.0 * (l->x[0] * (l->x[1] - sphere->coordinate[0]) + l->y[0] * (l->y[1] - sphere->coordinate[1]) + l->z[0] * (l->z[1] - sphere->coordinate[2]));
	coef[2] = (l->x[1] - sphere->coordinate[0]) * (l->x[1] - sphere->coordinate[0]) + (l->y[1] - sphere->coordinate[1]) * (l->y[1] - sphere->coordinate[1]) + (l->z[1] - sphere->coordinate[2]) * (l->z[1] - sphere->coordinate[2]) - (sphere->diameter / 2.0) * (sphere->diameter / 2.0);
	if (!(quadratic_equation(coef, answer)))
		return ;
	//answer <= 1 ignore ? 
	ct = -1;
	while (++ct < 2)
	{
		if (answer[ct] < 0.0)
			return ;
		if (is->intersect == 0 || answer[ct] < is->dist)
		{
			is->dist = answer[ct];
			is->intersect = 1;
			is->coordinate[0] = l->x[0] * is->dist + l->x[1];
			is->coordinate[1] = l->y[0] * is->dist + l->y[1];
			is->coordinate[2] = l->z[0] * is->dist + l->z[1];
			//change color
		}
	}
}


/*
typedef struct	s_sphere
{
	double			coordinate[3];
	double			diameter;
	int				color[3];
}				t_sphere;

typedef struct	s_line
{
	double	x[2];
	double	y[2];
	double	z[2];
}				t_line;

typedef struct	s_intersect
{
	int		intersect;
	double	coordinate[3];
	int		color[3];
}				t_intersect;
*/