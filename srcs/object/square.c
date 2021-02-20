#include "minirt.h"

t_square	*init_square(void)
{
	t_square	*square;
	int			ct;

	if (!(square = ft_malloc(1, sizeof(t_square))))
	{
		printf("ERROR_IN_INIT_SQUARE\n");
		return (NULL);
	}
	ct = -1;
	while (++ct < 3)
		square->coordinate[ct] = 0.0;
	ct = -1;
	while (++ct < 3)
		square->orientation[ct] = 0.0;
	square->side_size = 0.0;
	ct = -1;
	while (++ct < 3)
		square->color[ct] = 0;
	return (square);
}
