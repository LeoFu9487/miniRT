#include "../includes/minirt.h"

t_light	*init_light(void)
{
	int			cnt;
	t_light		*light;

	if (!(light = ft_malloc(1, sizeof(t_light))))
	{
		printf("ERROR_IN_INIT_LIGHT\n");
		return (NULL);
	}
	cnt = -1;
	while (++cnt < 3)
		light->coordinate[cnt] = 0.0;
	cnt = -1;
	while (++cnt < 3)
		light->color[cnt] = 0;
	light->brightness = 0.0;
	return (light);
}