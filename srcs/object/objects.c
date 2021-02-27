#include "minirt.h"

t_objects	*init_objects(t_parse_type type, void *add)
{
	t_objects	*obj;
	static int	num = 0;

	if (!(obj = ft_malloc(1, sizeof(t_objects))))
	{
		printf("ERROR_IN_INIT_OBJECTS\n");
		return (NULL);
	}
	obj->type = type;
	obj->ptr = add;
	obj->num = num++;
	return (obj);
}
