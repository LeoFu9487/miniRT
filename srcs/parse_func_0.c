#include "../includes/minirt.h"

void	parse_r(t_parse *parse, char *str)
{
	if (parse->rx || parse->ry)
		error_exit("Define render size multiple times!\n");
	parse->rx = (int)ft_atodouble(&str);
	parse->ry = (int)ft_atodouble(&str);
	if (parse->rx <= 0 || parse->ry <= 0)
		error_exit("couldn't find valid x and y rendering size\n");
}

void	parse_a(t_parse *parse, char *str)
{
	int		cnt;

	if (parse->aratio != -1.0 || parse->acolor[0] != -1 ||
	parse->acolor[1] != -1 || parse->acolor[2] != -1)
		error_exit("Define Ambient lightning multiple times\n");
	while (*str && ft_isdigit(*str) == 0 && *str != '.')
		str++;
	if (*str == 0)
		error_exit("couldn't find valid Ambient lightning ratio\n");
	parse->aratio = ft_atodouble(&str);
	if (parse->aratio < 0.0 || parse->aratio > 1.0)
		error_exit("couldn't find valid Ambient lightning ratio\n");
	cnt = -1;
	while (++cnt < 3)
	{
		while (*str && ft_isdigit(*str) == 0 && *str != '.')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid Ambient lightning color\n");
		parse->acolor[cnt] = (int)ft_atodouble(&str);
		if (parse->acolor[cnt] < 0 || parse->acolor[cnt] > 255)
			error_exit("couldn't find valid Ambient lightning color\n");
	}
}

void	parse_c(t_parse *parse, char *str)
{
	t_camera	*cam_info;
	int			ct;
	double		sign;

	if (!(cam_info = init_camera()))
	{
		printf("ERROR_IN_PARSE_C\n");
		return ;
	}
	ft_lstadd_back(&(parse->camera), ft_lstnew(cam_info));
	ct = -1;
	while (++ct < 3)
	{
		sign = 1.0;
		while (*str && ft_isdigit(*str) == 0 && *str != '.' && *str != '-')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid coordinate for cameras\n");
		if (*str == '-')
		{
			sign *= -1.0;
			if (!ft_isdigit(*(++str)))
				error_exit("find negative number in wrong format\n");
		}
		cam_info->coordinate[ct] = sign * ft_atodouble(&str);
	}
	ct = -1;
	while (++ct < 3)
	{
		sign = 1.0;
		while (*str && ft_isdigit(*str) == 0 && *str != '.' && *str != '-')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid orientation for cameras\n");
		if (*str == '-')
		{
			sign *= -1.0;
			if (!ft_isdigit(*(++str)))
				error_exit("find negative number in wrong format\n");
		}
		cam_info->orientation[ct] = sign * ft_atodouble(&str);
		if (cam_info->orientation[ct] < -1.0 || cam_info->orientation[ct] > 1.0)
			error_exit("Camera orientation out of range\n");
	}
	while (*str && ft_isdigit(*str) == 0 && *str != '.')
		str++;
	if (*str == 0)
		error_exit("couldn't find valid vof for cameras\n");
	cam_info->vof = ft_atodouble(&str);
	if (cam_info->vof < 0.0 || cam_info->vof > 180.0)
		error_exit("Camera vof out of range\n");
}

void	parse_l(t_parse *parse, char *str)
{
	t_light		*light_info;
	int			ct;
	double		sign;

	if (!(light_info = init_light()))
	{
		printf("ERROR_IN_PARSE_L\nABANDON THE LIGHT\n");
		return ;
	}
	ft_lstadd_front(&(parse->light), ft_lstnew(light_info));
	ct = -1;
	while (++ct < 3)
	{
		sign = 1.0;
		while (*str && ft_isdigit(*str) == 0 && *str != '.' && *str != '-')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid coordinate for lights\n");
		if (*str == '-')
		{
			sign *= -1.0;
			if (!ft_isdigit(*(++str)))
				error_exit("find negative number in wrong format\n");
		}
		light_info->coordinate[ct] = sign * ft_atodouble(&str);
	}
	while (*str && ft_isdigit(*str) == 0 && *str != '.')
		str++;
	if (*str == 0)
		error_exit("couldn't find valid brightness for light\n");
	light_info->brightness = ft_atodouble(&str);
	ct = -1;
	if (light_info->brightness < 0.0 || light_info->brightness > 1.0)
		error_exit("Light brightness out of range\n");
	while (++ct < 3)
	{
		while (*str && ft_isdigit(*str) == 0 && *str != '.')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid color for light\n");
		light_info->color[ct] = (int)ft_atodouble(&str);
		if (light_info->color[ct] < 0 || light_info->color[ct] > 255)
			error_exit("Light color out of range\n");
	}
}
