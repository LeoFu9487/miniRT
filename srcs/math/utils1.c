/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 22:57:11 by yfu               #+#    #+#             */
/*   Updated: 2021/03/03 00:50:54 by yfu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int			*get_obj_color(t_objects *obj)
{
	if (obj->type == sp)
		return (((t_sphere*)(obj->ptr))->color);
	if (obj->type == pl)
		return (((t_plane*)(obj->ptr))->color);
	if (obj->type == sq)
		return (((t_square*)(obj->ptr))->color);
	if (obj->type == cy)
		return (((t_cylinder*)(obj->ptr))->color);
	if (obj->type == tr)
		return (((t_triangle*)(obj->ptr))->color);
	if (obj->type == cu)
		return (((t_cube*)(obj->ptr))->color);
	if (obj->type == co)
		return (((t_cone*)(obj->ptr))->color);
	if (obj->type == py)
		return (((t_pyramid*)(obj->ptr))->square->color);
	return (NULL);
}

static t_objects	*get_obj(int **obj_color, t_intersect *it, t_parse *parse)
{
	t_list		*lst;
	t_objects	*obj;

	lst = parse->objects;
	while (lst)
	{
		obj = lst->content;
		if (obj->num == it->obj_num)
			break ;
		lst = lst->next;
	}
	if (!lst)
		error_exit("intersect_color1\n");
	*obj_color = get_obj_color(obj);
	return (obj);
}

static void			light_color(t_intersect *it, t_parse *parse,
double *cur_color, t_objects *obj)
{
	t_list	*lst;
	t_line	*line;
	int		*obj_color;
	double	*new_color;

	lst = parse->light;
	obj_color = get_obj_color(obj);
	while (lst)
	{
		if ((!(line = two_points_line(((t_light*)lst->content)->coordinate,
		it->coordinate))) || have_intersection(parse->objects, line))
		{
			ft_free(line);
			lst = lst->next;
			continue ;
		}
		new_color = reflection_color(obj_color, lst->content,
		get_new_brightness(obj, it, lst->content, parse));
		cur_color[0] += double_abs(new_color[0]);
		cur_color[1] += double_abs(new_color[1]);
		cur_color[2] += double_abs(new_color[2]);
		ft_free(new_color);
		ft_free(line);
		lst = lst->next;
	}
}

static void			flashlight_color(t_intersect *it, t_parse *parse,
double *cur_color, t_objects *obj)
{
	t_list	*lst;
	t_line	*line;
	double	*new_color;
	int		*obj_color;

	lst = parse->flashlight;
	obj_color = get_obj_color(obj);
	while (lst)
	{
		if ((!(in_flashlight_range(it->coordinate, lst->content))) || (!(line =
		two_points_line(((t_flashlight*)lst->content)->coordinate,
		it->coordinate))) || have_intersection(parse->objects, line))
		{
			lst = lst->next;
			continue ;
		}
		new_color = flashlight_reflection(obj_color,
		lst->content, flashlight_new_brightness(obj, it, lst->content, parse));
		cur_color[0] += double_abs(new_color[0]);
		cur_color[1] += double_abs(new_color[1]);
		cur_color[2] += double_abs(new_color[2]);
		ft_free(new_color);
		ft_free(line);
		lst = lst->next;
	}
}

void				intersect_color(t_intersect *it, t_parse *parse)
{
	int				*obj_color;
	int				ct;
	double			cur_color[3];
	int				color_max;
	t_objects		*obj;

	obj = get_obj(&obj_color, it, parse);
	ct = -1;
	while (++ct < 3)
	{
		it->color[ct] *= (int)((double)obj_color[ct] / 255.0);
		cur_color[ct] = 0.0;
	}
	light_color(it, parse, cur_color, obj);
	flashlight_color(it, parse, cur_color, obj);
	ct = -1;
	while (++ct < 3)
		it->color[ct] += (int)cur_color[ct];
	color_max = 255;
	ct = -1;
	while (++ct < 3)
		color_max = ft_max(color_max, it->color[ct]);
	ct = -1;
	while (++ct < 3)
		it->color[ct] = it->color[ct] * 255 / color_max;
}
