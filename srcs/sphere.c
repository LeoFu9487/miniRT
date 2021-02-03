#include "../includes/minirt.h"

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
