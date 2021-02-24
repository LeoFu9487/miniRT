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

t_line	*two_points_line(double	*p1, double	*p2)
{
	t_line	*line;

	if (!p1 || !p2 || (p1[0] == p2[0] && p1[1] == p2[1] && p1[2] == p2[2]) || !(line = ft_malloc(1, sizeof(t_line))))
		error_exit("two_points_line\n");
	line->x[1] = p1[0];
	line->y[1] = p1[1];
	line->z[1] = p1[2];
	line->x[0] = p2[0] - p1[0];
	line->y[0] = p2[1] - p1[1];
	line->z[0] = p2[2] - p1[2];
	return (line);
}

int		*reflection_color(int *color, t_light *light, double new_brightness)
{
	double	temp;
	int		*ans;
	int		ct;

	if (!(ans = ft_malloc(3, sizeof(int))))
		return (NULL);
	ct = -1;
	while (++ct < 3)
	{
		temp = (double)color[ct] * (double)(light->color[ct]) / 255.0 * new_brightness;
		ans[ct] = (int)temp;
	}
	return (ans);
}

double	linear_equation(double *coef, t_line *line)
{
	return (-1 * (coef[0] * line->x[1] + coef[1] * line->y[1] + coef[2] * line->z[1] + coef[3]) / (coef[0] * line->x[0] + coef[1] * line->y[0] + coef[2] * line->z[0]));
}
