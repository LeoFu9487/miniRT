/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 08:19:43 by yfu               #+#    #+#             */
/*   Updated: 2021/01/29 08:19:46 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** example :
** int *ptr = ft_memory(5, sizeof(int), NULL, push);
** ft_memory(0, 0, ptr, pop);
** ft_memory(0, 0, NULL, clear);
*/

void	*ft_malloc(size_t elem_cnt, size_t elem_size)
{
	return (ft_memory(elem_cnt, elem_size, NULL, push));
}

void	ft_free(void *del)
{
	ft_memory(0U, 0U, del, pop);
}

void	ft_free_all(void)
{
	ft_memory(0U, 0U, NULL, clear);
}

void	*ft_memory(size_t elem_cnt, size_t elem_size, void *del, t_memory type)
{
	static t_list	*head;
	void			*new_mem;

	if (type == push)
	{
		if (!(new_mem = ft_calloc(elem_cnt, elem_size)))
			ft_putstr_fd("ERROR_IN_FT_MEMORY_0\n", 1);
		else if (!(ft_lstadd_front(&head, ft_lstnew(new_mem))))
			ft_putstr_fd("ERROR_IN_FT_MEMORY_1\n", 1);
		return (new_mem);
	}
	if (type == pop)
		ft_lstdelone(&head, ft_lstfind(head, del), free);
	else
		ft_lstclear(&head, free);
	return (NULL);
}
