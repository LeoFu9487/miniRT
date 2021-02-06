#include "minirt.h"

t_cylinder	*init_cylinder(void)
{
	t_cylinder	*cylinder;
	int			ct;

	if (!(cylinder = ft_malloc(1, sizeof(t_cylinder))))
	{
		printf("Error\nERROR_IN_INIT_CYLINDER\n");
		return (NULL);
	}
	ct = -1;
	while (++ct < 3)
		cylinder->coordinate[ct] = 0.0;
	ct = -1;
	while (++ct < 3)
		cylinder->orientation[ct] = 0.0;
	ct = -1;
	while (++ct < 3)
		cylinder->color[ct] = 0;
	cylinder->diameter = 0.0;
	cylinder->height = 0.0;
	return (cylinder);
}
