#include "minirt.h"

/*
** utilisation : 
** double answer[2];
** double coef[3] = {1,2,3};
** int has_real_solutions = quadratic_equation(coef, answer);
*/

int	quadratic_equation(double *coef, double *answer)
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
