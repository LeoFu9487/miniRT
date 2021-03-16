/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 22:51:40 by yfu               #+#    #+#             */
/*   Updated: 2021/03/02 22:51:41 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		modify_length(double *vector, double length)
{
	double	multiply;
	int		ct;

	multiply = length / len(vector);
	ct = -1;
	while (++ct < 3)
		vector[ct] *= multiply;
}

t_line		*new_line(t_camera *camera, double *u, double *v, double *position)
{
	t_line	*line;

	if (!(line = ft_malloc(1, sizeof(t_line))))
		return (NULL);
	line->x[1] = camera->coordinate[0];
	line->y[1] = camera->coordinate[1];
	line->z[1] = camera->coordinate[2];
	line->x[0] = camera->orientation[0] +
	position[0] * u[0] + position[1] * v[0];
	line->y[0] = camera->orientation[1] +
	position[0] * u[1] + position[1] * v[1];
	line->z[0] = camera->orientation[2] +
	position[0] * u[2] + position[1] * v[2];
	return (line);
}

t_intersect	*init_intersect(t_parse *parse)
{
	t_intersect	*intersect;

	if (!(intersect = ft_malloc(1, sizeof(t_intersect))))
		return (NULL);
	intersect->intersect = 0;
	intersect->color[0] = (int)((double)parse->acolor[0]
	* parse->aratio * AMBIENT_LIGHT_INTENSITY);
	intersect->color[1] = (int)((double)parse->acolor[1]
	* parse->aratio * AMBIENT_LIGHT_INTENSITY);
	intersect->color[2] = (int)((double)parse->acolor[2]
	* parse->aratio / 10.0);
	intersect->dist = 1e300;
	return (intersect);
}

static void	assigned_func(void **func)
{
	func[(t_parse_type)sp] = &intersect_sp;
	func[(t_parse_type)pl] = &intersect_pl;
	func[(t_parse_type)sq] = &intersect_sq;
	func[(t_parse_type)cy] = &intersect_cy;
	func[(t_parse_type)tr] = &intersect_tr;
	func[(t_parse_type)cu] = &intersect_cu;
	func[(t_parse_type)co] = &intersect_co;
	func[(t_parse_type)py] = &intersect_py;
}

void		find_intersect(t_intersect *is, t_line *l, t_list *lst)
{
	void		(*func[12])(t_intersect*, t_line*, void*, int);
	t_objects	*obj;

	assigned_func((void**)func);
	while (lst)
	{
		obj = (t_objects*)(lst->content);
		func[obj->type](is, l, obj->ptr, obj->num);
		lst = lst->next;
	}
}
