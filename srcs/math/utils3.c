#include "minirt.h"

double	det(double **mat, int size)
{
	double	ans;
	double	**submat;
	int		ct[1];

	if (size == 1)
		return (mat[0][0]);
	ans = 0.0;
	ct[0] = -1;
	submat = ft_malloc((size - 1), sizeof(double*));
	while (++ct[0] < size - 1)
		submat[ct[0]] = &(mat[ct[0] + 1][1]);
	ct[0] = -1;
	while (++ct[0] < size)
	{
		if (ct[0] % 2)
			ans -= mat[ct[0]][0] * det(submat, size - 1);
		else
			ans += mat[ct[0]][0] * det(submat, size - 1);
		submat[ct[0]] = &(mat[ct[0]][1]);
	}
	ft_free(submat);
	return (ans);
}