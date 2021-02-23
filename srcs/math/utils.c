#include "minirt.h"

/*
** utilisation : 
** double answer[2];
** double coef[3] = {1,2,3};
** int has_real_solutions = quadratic_equation(coef, answer);
*/

int		quadratic_equation(double *coef, double *answer)
{
	double	det;

	if (!coef || !answer)
		return (-1);
	det = coef[1] * coef[1] - 4 * coef[0] * coef[2];
	if (det < 0.0)
		return (0);
	answer[0] = (-1.0 * coef[1] + sqrt(det)) / (2.0 * coef[0]);
	answer[1] = (-1.0 * coef[1] - sqrt(det)) / (2.0 * coef[0]);
	return (1);
}

t_line	*two_points(double	*p1, double	*p2)
{
	t_line	*line;

	if (!p1 || !p2 || (p1[0] == p2[0] && p1[1] == p2[1] && p1[2] == p2[2]) || !(line = ft_malloc(1, sizeof(t_line))))
		return (NULL);
	line->x[1] = p1[0];
	line->y[1] = p1[1];
	line->z[1] = p1[2];
	line->x[0] = p2[0] - p1[0];
	line->y[0] = p2[1] - p1[1];
	line->z[0] = p2[2] - p1[2];
	return (line);
}

void	assigned_func(void **func)
{
	func[sp] = &have_intersection_sp;
	func[pl] = &have_intersection_pl;
	func[cy] = &have_intersection_cy;
	func[tr] = &have_intersection_tr;
	func[sq] = &have_intersection_sq;
}

int		have_intersection(t_list *lst, t_line *line)
{
	t_objects	*objs;
	int			(*func[9])(t_line*, void*);

	assigned_func((void**)func);
	while (lst)
	{
		objs = lst->content;
		if (func[objs->type](line, objs->ptr))
			return (1);
		lst = lst->next;
	}
	return (0);
}

void	intersect_color(t_intersect *it, t_parse *parse)
{
	t_light	*light;
	t_list	*lst;

	lst = parse->light;
	while (lst)
	{
		light = lst->content;
		lst = lst->next;
		if (have_intersection(parse->objects, two_points(light->coordinate, it->coordinate)))
			continue ;
		it->color[2] = 255;
		/*
		do colors
		*/
	}
}


int				have_intersection_pl(t_line *l, void *ptr)
{
	(void)l;(void)ptr;
	return (0);
}
int				have_intersection_sq(t_line *l, void *ptr)
{
		(void)l;(void)ptr;

	return (0);
}
int				have_intersection_cy(t_line *l, void *ptr)
{	(void)l;(void)ptr;

	return (0);
}
int				have_intersection_tr(t_line *l, void *ptr)
{	(void)l;(void)ptr;

	return (0);
}
