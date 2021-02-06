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