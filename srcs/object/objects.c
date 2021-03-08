/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 02:29:44 by yfu               #+#    #+#             */
/*   Updated: 2021/03/08 14:28:12 by yfu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_objects	*init_objects(t_parse_type type, void *add)
{
	t_objects	*obj;
	static int	num = 0;

	if (!(obj = ft_malloc(1, sizeof(t_objects))))
		error_exit("OBJECTS\n");
	obj->type = type;
	obj->ptr = add;
	obj->num = num++;
	return (obj);
}
