#include "minirt.h"

static double	ft_abs_f(double a)
{
	return (a < 0.0 ? -1.0 * a : a);
}

void			parse_r(t_parse *parse, char *str)
{
	if (parse->rx || parse->ry)
		error_exit("Define render size multiple times!\n");
	parse->rx = (int)ft_atodouble(&str);
	parse->ry = (int)ft_atodouble(&str);
	if (parse->rx <= 0 || parse->ry <= 0)
		error_exit("invalid rendering size\n");
}

void			parse_a(t_parse *parse, char *str)
{
	int		cnt;

	if (parse->aratio != -1.0 || parse->acolor[0] != -1 ||
	parse->acolor[1] != -1 || parse->acolor[2] != -1)
		error_exit("Define Ambient lighting multiple times\n");
	while (*str && ft_isdigit(*str) == 0 && *str != '.')
		str++;
	if (*str == 0)
		error_exit("Ambient lighting ratio not found\n");
	parse->aratio = ft_atodouble(&str);
	if (parse->aratio < 0.0 || parse->aratio > 1.0)
		error_exit("Ambient lighting ratio invalid\n");
	cnt = -1;
	while (++cnt < 3)
	{
		while (*str && ft_isdigit(*str) == 0 && *str != '.')
			str++;
		if (*str == 0)
			error_exit("Ambient lighting color not found\n");
		parse->acolor[cnt] = (int)ft_atodouble(&str);
		if (parse->acolor[cnt] < 0 || parse->acolor[cnt] > 255)
			error_exit("Ambient lighting color invalid\n");
	}
}

void			parse_c(t_parse *parse, char *str)
{
	t_camera	*cam_info;
	int			ct;

	if (!(cam_info = init_camera()))
	{
		printf("Error : not able to malloc\nabandon this line : \n%s\n", str);
		return ;
	}
	ft_lstadd_back(&(parse->camera), ft_lstnew(cam_info));
	ct = -1;
	while (++ct < 3)
		cam_info->coordinate[ct] = ft_neg_double(&str, "coordinate of camera");
	ct = -1;
	while (++ct < 3)
		cam_info->orientation[ct] = ft_neg_double(&str, "camera orientation");
	if (ft_abs_f(cam_info->orientation[0]) > 1.0 || ft_abs_f(
	cam_info->orientation[1]) > 1.0 || ft_abs_f(cam_info->orientation[2]) > 1.0)
		error_exit("Camera orientation out of range\n");
	while (*str && ft_isdigit(*str) == 0 && *str != '.')
		str++;
	if (*str == 0)
		error_exit("camera vof not found\n");
	cam_info->vof = ft_atodouble(&str);
	if (cam_info->vof < 0.0 || cam_info->vof > 180.0)
		error_exit("camera vof out of range\n");
}

void			parse_l(t_parse *parse, char *str)
{
	t_light		*light_info;
	int			ct;

	if (!(light_info = init_light()))
	{
		printf("Error : not able to malloc\nabandon this line %s\n", str);
		return ;
	}
	ft_lstadd_front(&(parse->light), ft_lstnew(light_info));
	ct = -1;
	while (++ct < 3)
		light_info->coordinate[ct] = ft_neg_double(&str, "coordinate of light");
	while (*str && ft_isdigit(*str) == 0 && *str != '.')
		str++;
	if (*str == 0)
		error_exit("brightness for light not found\n");
	light_info->brightness = ft_atodouble(&str);
	ct = -1;
	if (light_info->brightness < 0.0 || light_info->brightness > 1.0)
		error_exit("brightness of light out of range\n");
	while (++ct < 3)
	{
		while (*str && ft_isdigit(*str) == 0 && *str != '.')
			str++;
		if (*str == 0)
			error_exit("color for light not found\n");
		light_info->color[ct] = (int)ft_atodouble(&str);
		if (light_info->color[ct] < 0 || light_info->color[ct] > 255)
			error_exit("Light color out of range\n");
	}
}
