#include "minirt.h"

t_flashlight	*init_flashlight(void)
{
	t_flashlight	*flashlight;

	if (!(flashlight = ft_malloc(1, sizeof(t_flashlight))))
		error_exit("init_flashlight\n");
	return (flashlight);
}

int				in_flashlight_range(double *p0, t_flashlight *flashlight)
{
	double	*p1;
	double	t;

	t = (dot(flashlight->orientation, p0) - dot(flashlight->orientation, flashlight->coordinate)) / (len(flashlight->orientation) * len(flashlight->orientation));
	if (t < 1e-6)
		return (0);
	p1 = make_point(flashlight->coordinate[0] + flashlight->orientation[0] * t, flashlight->coordinate[1] + flashlight->orientation[1] * t, flashlight->coordinate[2] + flashlight->orientation[2] * t);
	if (two_points_distance(p0, p1) <= flashlight->diameter / 2.0 - 1e-6)
	{
		ft_free(p1);
		return (1);
	}
	ft_free(p1);
	return (0);
}
