/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 22:52:13 by yfu               #+#    #+#             */
/*   Updated: 2021/03/02 23:07:22 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void		assigned_func(void **func)
{
	func[sp] = &normal_vector_sp;
	func[pl] = &normal_vector_pl;
	func[tr] = &normal_vector_tr;
	func[cy] = &normal_vector_cy;
	func[sq] = &normal_vector_sq;
	func[cu] = &normal_vector_cu;
	func[co] = &normal_vector_co;
	func[py] = &normal_vector_py;
}

double			get_new_brightness(t_objects *obj, t_intersect *it,
t_light *light, t_parse *parse)
{
	double	ans;
	double	*(*func[12])(double*, void*);
	double	*vector[3];
	double	len_sum;

	ans = light->brightness;
	len_sum = two_points_distance(it->coordinate, light->coordinate) +
	two_points_distance(it->coordinate,
	((t_camera*)(parse->cur_camera->content))->coordinate);
	len_sum /= LEN_UNIT;
	ans /= len_sum * len_sum;
	assigned_func((void**)func);
	vector[0] = func[obj->type](it->coordinate, obj->ptr);
	vector[1] = two_points_vector(it->coordinate,
	((t_camera*)(parse->cur_camera->content))->coordinate);
	vector[2] = two_points_vector(it->coordinate, light->coordinate);
	ans *= cos_vector(vector[0], vector[2]);
	ft_free(vector[0]);
	ft_free(vector[1]);
	ft_free(vector[2]);
	(void)obj;
	return (double_abs(ans));
}

double			flashlight_new_brightness(t_objects *obj, t_intersect *it,
t_flashlight *flashlight, t_parse *parse)
{
	double	ans;
	double	*(*func[12])(double*, void*);
	double	*vector[3];
	double	len_sum;

	ans = flashlight->brightness;
	len_sum = two_points_distance(it->coordinate, flashlight->coordinate) +
	two_points_distance(it->coordinate,
	((t_camera*)(parse->cur_camera->content))->coordinate);
	len_sum /= LEN_UNIT;
	ans /= len_sum * len_sum;
	assigned_func((void**)func);
	vector[0] = func[obj->type](it->coordinate, obj->ptr);
	vector[1] = two_points_vector(it->coordinate,
	((t_camera*)(parse->cur_camera->content))->coordinate);
	vector[2] = two_points_vector(it->coordinate, flashlight->coordinate);
	ans *= cos_vector(vector[0], vector[2]);
	ft_free(vector[0]);
	ft_free(vector[1]);
	ft_free(vector[2]);
	(void)obj;
	return (double_abs(ans));
}

static void		assigned_func2(void **func)
{
	func[sp] = &have_intersection_sp;
	func[pl] = &have_intersection_pl;
	func[cy] = &have_intersection_cy;
	func[tr] = &have_intersection_tr;
	func[sq] = &have_intersection_sq;
	func[cu] = &have_intersection_cu;
	func[co] = &have_intersection_co;
	func[py] = &have_intersection_py;
}

int				have_intersection(t_list *lst, t_line *line)
{
	t_objects	*objs;
	int			(*func[12])(t_line*, void*);

	assigned_func2((void**)func);
	while (lst)
	{
		objs = lst->content;
		if (func[objs->type](line, objs->ptr))
			return (1);
		lst = lst->next;
	}
	return (0);
}
