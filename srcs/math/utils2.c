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

double	*reflection_color(int *color, t_light *light, double new_brightness)
{
	double	*ans;
	int		ct;

	if (!(ans = ft_malloc(3, sizeof(double))))
		error_exit("reflection_color\n");
	ct = -1;
	while (++ct < 3)
		ans[ct] = (double)color[ct] * (double)(light->color[ct]) / 255.0 * new_brightness;
	return (ans);
}

double	*flashlight_reflection(int *color, t_flashlight *flashlight, double new_brightness)
{
	double	*ans;
	int		ct;

	if (!(ans = ft_malloc(3, sizeof(double))))
		error_exit("reflection_color\n");
	ct = -1;
	while (++ct < 3)
		ans[ct] = (double)color[ct] * (double)(flashlight->color[ct]) / 255.0 * new_brightness;
	return (ans);
}

void	linear_equations(double *u, double *v, double *w, double *ans)
{
	int		ct[3];

	ct[0] = -1;
	ct[2] = 1;
	while (ct[2] && ++ct[0] < 3)
	{
		ct[1] = -1;
		while (ct[2] && ++ct[1] < 3)
		{
			if (ct[0] == ct[1] || u[ct[0]] == 0.0 || v[ct[0]] * u[ct[1]] - u[ct[0]] * v[ct[1]] == 0.0)
				continue ;
			ct[2] = 0;
		}
	}
	if (ct[2])
		error_exit("linear_equations\n");
	ans[1] = (w[ct[0]] * u[ct[1]] - u[ct[0]] * w[ct[1]]) / (v[ct[0]] * u[ct[1]] - u[ct[0]] * v[ct[1]]);
	ans[0] = (w[ct[0]] - v[ct[0]] * ans[1]) / u[ct[0]];

}

double	linear_equation(double *coef, t_line *line)
{
	return (-1 * (coef[0] * line->x[1] + coef[1] * line->y[1] + coef[2] * line->z[1] + coef[3]) / (coef[0] * line->x[0] + coef[1] * line->y[0] + coef[2] * line->z[0]));
}
