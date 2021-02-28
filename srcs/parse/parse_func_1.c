#include "minirt.h"

void	parse_sp(t_parse *parse, char *str)
{
	t_sphere	*sphere_info;
	int			ct;
	double		sign;

	if (!(sphere_info = init_sphere()))
	{
		printf("Error : not able to malloc\nabandon this line %s\n", str);
		return ;
	}
	ft_lstadd_back(&(parse->objects), ft_lstnew(init_objects(sp, sphere_info)));
	ct = -1;
	while (++ct < 3)
	{
		sign = 1.0;
		while (*str && ft_isdigit(*str) == 0 && *str != '.' && *str != '-')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid orientation for sphere\n");
		if (*str == '-')
		{
			sign *= -1.0;
			if (!ft_isdigit(*(++str)))
				error_exit("find negative number in wrong format\n");
		}
		sphere_info->coordinate[ct] = sign * ft_atodouble(&str);
	}
	while (*str && ft_isdigit(*str) == 0 && *str != '.')
		str++;
	if (*str == 0)
		error_exit("couldn't find valid diameter for sphere\n");
	sphere_info->diameter = ft_atodouble(&str);
	ct = -1;
	if (sphere_info->diameter < 0.0)
		error_exit("negative diameter for sphere\n");
	while (++ct < 3)
	{
		while (*str && ft_isdigit(*str) == 0 && *str != '.')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid color for sphere\n");
		sphere_info->color[ct] = (int)ft_atodouble(&str);
		if (sphere_info->color[ct] < 0 || sphere_info->color[ct] > 255)
			error_exit("sphere color out of range\n");
	}
}

void	parse_pl(t_parse *parse, char *str)
{
	t_plane	*plane_info;
	int		ct;
	double	sign;

	if (!(plane_info = init_plane()))
	{
		printf("Error : not able to malloc\nabandon this line %s\n", str);
		return ;
	}
	ft_lstadd_back(&(parse->objects), ft_lstnew(init_objects(pl, plane_info)));
	ct = -1;
	while (++ct < 3)
	{
		sign = 1.0;
		while (*str && ft_isdigit(*str) == 0 && *str != '.' && *str != '-')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid orientation for plane\n");
		if (*str == '-')
		{
			sign *= -1.0;
			if (!ft_isdigit(*(++str)))
				error_exit("find negative number in wrong format\n");
		}
		plane_info->coordinate[ct] = sign * ft_atodouble(&str);
	}
	ct = -1;
	while (++ct < 3)
	{
		sign = 1.0;
		while (*str && ft_isdigit(*str) == 0 && *str != '.' && *str != '-')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid orientation for plane\n");
		if (*str == '-')
		{
			sign *= -1.0;
			if (!ft_isdigit(*(++str)))
				error_exit("find negative number in wrong format\n");
		}
		plane_info->orientation[ct] = sign * ft_atodouble(&str);
		if (plane_info->orientation[ct] < -1.0 || plane_info->orientation[ct] > 1.0)
			error_exit("Plane orientation out of range\n");
	}
	ct = -1;
	while (++ct < 3)
	{
		while (*str && ft_isdigit(*str) == 0 && *str != '.')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid color for plane\n");
		plane_info->color[ct] = (int)ft_atodouble(&str);
		if (plane_info->color[ct] < 0 || plane_info->color[ct] > 255)
			error_exit("Plane color out of range\n");
	}
}

void	parse_sq(t_parse *parse, char *str)
{
	t_square	*square_info;
	int			ct;
	double		sign;
	double		base_v[3];

	if (!(square_info = init_square()))
	{
		printf("Error : not able to malloc\nabandon this line %s\n", str);
		return ;
	}
	ft_lstadd_back(&(parse->objects), ft_lstnew(init_objects(sq, square_info)));
	ct = -1;
	while (++ct < 3)
	{
		sign = 1.0;
		while (*str && ft_isdigit(*str) == 0 && *str != '.' && *str != '-')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid coordinate for square\n");
		if (*str == '-')
		{
			sign *= -1.0;
			if (!ft_isdigit(*(++str)))
				error_exit("find negative number in wrong format\n");
		}
		square_info->coordinate[ct] = sign * ft_atodouble(&str);
	}
	ct = -1;
	while (++ct < 3)
	{
		sign = 1.0;
		while (*str && ft_isdigit(*str) == 0 && *str != '.' && *str != '-')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid orientation for square\n");
		if (*str == '-')
		{
			sign *= -1.0;
			if (!ft_isdigit(*(++str)))
				error_exit("find negative number in wrong format\n");
		}
		square_info->orientation[ct] = sign * ft_atodouble(&str);
		if (square_info->orientation[ct] < -1.0 || square_info->orientation[ct] > 1.0)
			error_exit("Square orientation out of range\n");
	}
	while (*str && ft_isdigit(*str) == 0 && *str != '.')
		str++;
	if (*str == 0)
		error_exit("couldn't find valid side_size for square\n");
	square_info->side_size = ft_atodouble(&str);
	ct = -1;
	while (++ct < 3)
	{
		while (*str && ft_isdigit(*str) == 0 && *str != '.')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid color for square\n");
		square_info->color[ct] = (int)ft_atodouble(&str);
		if (square_info->color[ct] < 0 || square_info->color[ct] > 255)
			error_exit("Square color out of range\n");
	}
	base_v[0] = 0.0;
	if (square_info->orientation[1] == 0.0 && square_info->orientation[0] == 0.0)
		base_v[1] = 1.0;
	else
		base_v[1] = 0.0;
	base_v[2] = 1.0 - base_v[1];
	square_info->vector[0] = cross(base_v, square_info->orientation);
	square_info->vector[1] = cross(square_info->vector[0], square_info->orientation);
	modify_length(square_info->vector[0], square_info->side_size);
	modify_length(square_info->vector[1], square_info->side_size);
	ct = -1;
	while (++ct < 3)
		square_info->start_point[ct] = square_info->coordinate[ct] - square_info->vector[0][ct] / 2.0 - square_info->vector[1][ct] / 2.0;
}

void	parse_cy(t_parse *parse, char *str)
{
	t_cylinder	*cylinder_info;
	int			ct;
	double		sign;

	if (!(cylinder_info = init_cylinder()))
	{
		printf("Error : not able to malloc\nabandon this line %s\n", str);
		return ;
	}
	ft_lstadd_back(&(parse->objects), ft_lstnew(init_objects(cy, cylinder_info)));
	ct = -1;
	while (++ct < 3)
	{
		sign = 1.0;
		while (*str && ft_isdigit(*str) == 0 && *str != '.' && *str != '-')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid coordinate for cylinder\n");
		if (*str == '-')
		{
			sign *= -1.0;
			if (!ft_isdigit(*(++str)))
				error_exit("find negative number in wrong format\n");
		}
		cylinder_info->coordinate[ct] = sign * ft_atodouble(&str);
	}
	ct = -1;
	while (++ct < 3)
	{
		sign = 1.0;
		while (*str && ft_isdigit(*str) == 0 && *str != '.' && *str != '-')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid orientation for cylinder\n");
		if (*str == '-')
		{
			sign *= -1.0;
			if (!ft_isdigit(*(++str)))
				error_exit("find negative number in wrong format\n");
		}
		cylinder_info->orientation[ct] = sign * ft_atodouble(&str);
		if (cylinder_info->orientation[ct] < -1.0 || cylinder_info->orientation[ct] > 1.0)
			error_exit("Cylinder orientation out of range\n");
	}
	while (*str && ft_isdigit(*str) == 0 && *str != '.')
		str++;
	if (*str == 0)
		error_exit("couldn't find valid diameter for cylinder\n");
	cylinder_info->diameter = ft_atodouble(&str);
	while (*str && ft_isdigit(*str) == 0 && *str != '.')
		str++;
	if (*str == 0)
		error_exit("couldn't find valid height for cylinder\n");
	cylinder_info->height = ft_atodouble(&str);
	ct = -1;
	while (++ct < 3)
	{
		while (*str && ft_isdigit(*str) == 0 && *str != '.')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid color for cylinder\n");
		cylinder_info->color[ct] = (int)ft_atodouble(&str);
		if (cylinder_info->color[ct] < 0 || cylinder_info->color[ct] > 255)
			error_exit("Cylinder color out of range\n");
	}
	modify_length(cylinder_info->orientation, cylinder_info->height / 2.0);
	cylinder_info->end_point[1] = two_points_vector(cylinder_info->orientation, cylinder_info->coordinate);
	modify_length(cylinder_info->orientation, -1.0 * cylinder_info->height);
	cylinder_info->end_point[0] = two_points_vector(cylinder_info->orientation, cylinder_info->end_point[1]);
	cylinder_info->middle_line = two_points_line(cylinder_info->end_point[0], cylinder_info->end_point[1]);
}

void	parse_tr(t_parse *parse, char *str)
{
	t_triangle	*triangle_info;
	int			ct[2];
	double		sign;

	if (!(triangle_info = init_triangle()))
	{
		printf("Error : not able to malloc\nabandon this line %s\n", str);
		return ;
	}
	ft_lstadd_back(&(parse->objects), ft_lstnew(init_objects(tr, triangle_info)));
	ct[0] = -1;
	while (++ct[0] < 3)
	{
		ct[1] = -1;
		while (++ct[1] < 3)
		{
			sign = 1.0;
			while (*str && ft_isdigit(*str) == 0 && *str != '.' && *str != '-')
				str++;
			if (*str == 0)
				error_exit("couldn't find valid coordinate for triangle\n");
			if (*str == '-')
			{
				sign *= -1.0;
				if (!ft_isdigit(*(++str)))
					error_exit("find negative number in wrong format\n");
			}
			triangle_info->point[ct[0]][ct[1]] = sign * ft_atodouble(&str);
		}
	}
	ct[0] = -1;
	while (++ct[0] < 3)
	{
		while (*str && ft_isdigit(*str) == 0 && *str != '.')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid color for triangle\n");
		triangle_info->color[ct[0]] = (int)ft_atodouble(&str);
		if (triangle_info->color[ct[0]] < 0 || triangle_info->color[ct[0]] > 255)
			error_exit("triangle color out of range\n");
	}
	triangle_info->vector[0] = two_points_vector(triangle_info->point[0], triangle_info->point[1]);
	triangle_info->vector[1] = two_points_vector(triangle_info->point[0], triangle_info->point[2]);
	if (!(triangle_info->orientation = cross(triangle_info->vector[0], triangle_info->vector[1])))
		error_exit("parse_tr\n");
	if (triangle_info->orientation[0] == 0.0 && triangle_info->orientation[1] == 0.0 && triangle_info->orientation[2] == 0.0)
		error_exit("invalid points of triangle : form a line instead of a triangle\n");
}

void	parse_cu(t_parse *parse, char *str)
{
	t_cube	*cube;
	int		ct;
	double	sign;

	if (!(cube = init_cube()))
		error_exit("parse_cu\n");
	ft_lstadd_back(&(parse->objects), ft_lstnew(init_objects(cu, cube)));
	ct = -1;
	while (++ct < 3)
	{
		sign = 1.0;
		while (*str && ft_isdigit(*str) == 0 && *str != '.' && *str != '-')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid coordinate for cube\n");
		if (*str == '-')
		{
			sign *= -1.0;
			if (!ft_isdigit(*(++str)))
				error_exit("find negative number in wrong format\n");
		}
		cube->coordinate[ct] = sign * ft_atodouble(&str);
	}
	while (*str && ft_isdigit(*str) == 0 && *str != '.')
		str++;
	if (*str == 0)
		error_exit("couldn't find valid side_size for cube\n");
	cube->side_size = ft_atodouble(&str);
	ct = -1;
	while (++ct < 3)
	{
		while (*str && ft_isdigit(*str) == 0 && *str != '.')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid color for cube\n");
		cube->color[ct] = (int)ft_atodouble(&str);
		if (cube->color[ct] < 0 || cube->color[ct] > 255)
			error_exit("cube color out of range\n");
	}
	compose_cube(cube);
}

void	parse_co(t_parse *parse, char *str)
{
	t_cone		*cone;
	int			ct;
	double		sign;

	if (!(cone = init_cone()))
	{
		printf("Error : not able to malloc\nabandon this line %s\n", str);
		return ;
	}
	ft_lstadd_back(&(parse->objects), ft_lstnew(init_objects(co, cone)));
	ct = -1;
	while (++ct < 3)
	{
		sign = 1.0;
		while (*str && ft_isdigit(*str) == 0 && *str != '.' && *str != '-')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid coordinate for coner\n");
		if (*str == '-')
		{
			sign *= -1.0;
			if (!ft_isdigit(*(++str)))
				error_exit("find negative number in wrong format\n");
		}
		cone->coordinate[ct] = sign * ft_atodouble(&str);
	}
	ct = -1;
	while (++ct < 3)
	{
		sign = 1.0;
		while (*str && ft_isdigit(*str) == 0 && *str != '.' && *str != '-')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid orientation for cone\n");
		if (*str == '-')
		{
			sign *= -1.0;
			if (!ft_isdigit(*(++str)))
				error_exit("find negative number in wrong format\n");
		}
		cone->orientation[ct] = sign * ft_atodouble(&str);
		if (cone->orientation[ct] < -1.0 || cone->orientation[ct] > 1.0)
			error_exit("Cone orientation out of range\n");
	}
	while (*str && ft_isdigit(*str) == 0 && *str != '.')
		str++;
	if (*str == 0)
		error_exit("couldn't find valid diameter for cone\n");
	cone->diameter = ft_atodouble(&str);
	while (*str && ft_isdigit(*str) == 0 && *str != '.')
		str++;
	if (*str == 0)
		error_exit("couldn't find valid height for cone\n");
	cone->height = ft_atodouble(&str);
	ct = -1;
	while (++ct < 3)
	{
		while (*str && ft_isdigit(*str) == 0 && *str != '.')
			str++;
		if (*str == 0)
			error_exit("couldn't find valid color for cone\n");
		cone->color[ct] = (int)ft_atodouble(&str);
		if (cone->color[ct] < 0 || cone->color[ct] > 255)
			error_exit("Cone color out of range\n");
	}
	modify_length(cone->orientation, cone->height / 2.0);
	cone->end_point[1] = two_points_vector(cone->orientation, cone->coordinate);
	modify_length(cone->orientation, -1.0 * cone->height);
	cone->end_point[0] = two_points_vector(cone->orientation, cone->end_point[1]);
}
