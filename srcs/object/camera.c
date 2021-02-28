#include "minirt.h"

t_camera	*init_camera(void)
{
	int			cnt;
	t_camera	*cam;
	static int	num = 0;

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
	cam->num = num++;
	cam->distance_to_screen = 0.0;
	cnt = -1;
	while (++cnt < 8)
	{
		cam->img_ptr[cnt] = NULL;
		if (!(cam->bits_per_pixel[cnt] = ft_malloc(1, sizeof(int))))
			error_exit("INIT_CAMERA_0\n");
		if (!(cam->size_line[cnt] = ft_malloc(1, sizeof(int))))
			error_exit("INIT_CAMERA_1\n");
		if (!(cam->endian[cnt] = ft_malloc(1, sizeof(int))))
			error_exit("INIT_CAMERA_2\n");
	}
	return (cam);
}
