#include "minirt.h"

static void	assigned_func(void **func)
{
	func[sp] = &have_intersection_sp;
	func[pl] = &have_intersection_pl;
	func[cy] = &have_intersection_cy;
	func[tr] = &have_intersection_tr;
	func[sq] = &have_intersection_sq;
}

int			have_intersection(t_list *lst, t_line *line)
{
	t_objects	*objs;
	int			(*func[9])(t_line*, void*);

	assigned_func((void**)func);
	while (lst)
	{
		objs = lst->content;
		if (func[objs->type](line, objs->ptr))
			return (1);
		lst = lst->next;
	}
	return (0);
}

static int	*get_obj_color(t_objects *obj)
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
	return (NULL);
}

static void		assigned_func2(void **func)
{
	func[sp] = &normal_vector_sp;
	func[pl] = &normal_vector_pl;
	func[tr] = &normal_vector_tr;
	func[cy] = &normal_vector_cy;
	func[sq] = &normal_vector_sq;
}

static double	get_new_brightness(t_objects *obj, t_intersect *it, t_light *light, t_parse *parse)
{
	double	ans;
	double	*(*func[9])(double*, void*);
	double	*vector[3];
	double	len_sum;

	ans = light->brightness;
	len_sum = two_points_distance(it->coordinate, light->coordinate) + two_points_distance(it->coordinate, ((t_camera*)(parse->cur_camera->content))->coordinate);
	len_sum /= LEN_UNIT;
	ans /= len_sum * len_sum;
	assigned_func2((void**)func);
	vector[0] = func[obj->type](it->coordinate, obj->ptr);
	vector[1] = two_points_vector(it->coordinate, ((t_camera*)parse->cur_camera->content)->coordinate);
	vector[2] = two_points_vector(it->coordinate, light->coordinate);
	ans *= cos(acos(cos_vector(vector[0], vector[1])) - acos(cos_vector(vector[0], vector[2])));
	if (ans < 0.0)
		ans *= -1.0;
	ft_free(vector[0]);
	ft_free(vector[1]);
	ft_free(vector[2]);
	(void)obj;
	return (ans);
}

void		intersect_color(t_intersect *it, t_parse *parse)
{
	t_light		*light;
	int			*obj_color;
	t_list		*lst;
	t_line		*line;
	int			ct;
	double		*new_color;
	double		cur_color[3];
	int			color_max;
	double		new_brightness;
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
	obj_color = get_obj_color(obj);
	ct = -1;
	while (++ct < 3)
		it->color[ct] *= (int)((double)obj_color[ct] / 255.0);
	ct = -1;
	while (++ct < 3)
		cur_color[ct] = 0.0;
	lst = parse->light;
	while (lst)
	{
		light = lst->content;
		lst = lst->next;
		if (!(line = two_points_line(light->coordinate, it->coordinate)))
			error_exit("intersect_color3\n");
		if (have_intersection(parse->objects, line))
			continue ;
		new_brightness = get_new_brightness(obj, it, light, parse);
		if (!(new_color = reflection_color(obj_color, light, new_brightness)))
			error_exit("intersect_color2\n");
		ct = -1;
		while (++ct < 3)
			cur_color[ct] += new_color[ct];
		ft_free(new_color);
		ft_free(line);
	}
	ct = -1;
	while (++ct < 3)
		it->color[ct] += (int)cur_color[ct];
	color_max = 0;
	ct = -1;
	while (++ct < 3)
		color_max = ft_max(color_max, it->color[ct]);
	ct = -1;
	if (color_max > 255)
		while (++ct < 3)
			it->color[ct] = it->color[ct] * 255 / color_max;
}
