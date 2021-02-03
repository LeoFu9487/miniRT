#include "../includes/minirt.h"

t_camera	*init_camera(void)
{
	int			cnt;
	t_camera	*cam;

	if (!(cam = ft_malloc(1, sizeof(t_camera))))
	{
		printf("ERROR_IN_INIT_CAMERA\n");
		return (NULL);
	}
	cnt = -1;
	while (++cnt < 3)
		cam->coordinate[cnt] = 0.0;
	cnt = -1;
	while (++cnt < 3)
		cam->orientation[cnt] = 0.0;
	cam->vof = 0;
	return (cam);
}
