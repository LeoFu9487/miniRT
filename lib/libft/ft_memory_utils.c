#include "libft.h"

void			*ft_malloc(size_t elem_cnt, size_t elem_size)
{
	return (ft_memory(elem_cnt, elem_size, NULL, push));
}

void			ft_free(void *del)
{
	ft_memory(0U, 0U, del, pop);
}

void			ft_free_all(void)
{
	ft_memory(0U, 0U, NULL, clear);
}
