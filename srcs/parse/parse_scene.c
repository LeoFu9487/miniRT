#include "minirt.h"

t_parse		*init_parse(void)
{
	t_parse	*parse;

	if (!(parse = ft_malloc(1, sizeof(t_parse))))
	{
		printf("ERROR_IN_INIT_PARSE\n");
		return (NULL);
	}
	parse->rx = 0;
	parse->ry = 0;
	parse->objects = NULL;
	parse->light = NULL;
	parse->camera = NULL;
	parse->cur_camera = NULL;
	parse->aratio = -1.0;
	parse->acolor[0] = -1;
	parse->acolor[1] = -1;
	parse->acolor[2] = -1;
	return (parse);
}

static int	parse_type(char *str)
{
	char	*s;

	s = ft_substr(str, 0, 2);
	if (ft_strncmp(s, "sp", 2) == 0)
		return ((t_parse_type)sp);
	if (ft_strncmp(s, "pl", 2) == 0)
		return ((t_parse_type)pl);
	if (ft_strncmp(s, "sq", 2) == 0)
		return ((t_parse_type)sq);
	if (ft_strncmp(s, "cy", 2) == 0)
		return ((t_parse_type)cy);
	if (ft_strncmp(s, "tr", 2) == 0)
		return ((t_parse_type)tr);
	if (ft_strncmp(s, "cu", 2) == 0)
		return ((t_parse_type)cu);
	if (ft_strncmp(s, "co", 2) == 0)
		return ((t_parse_type)co);
	ft_free(s);
	s = ft_substr(str, 0, 1);
	if (ft_strncmp(s, "R", 1) == 0)
		return ((t_parse_type)R);
	if (ft_strncmp(s, "A", 1) == 0)
		return ((t_parse_type)A);
	if (ft_strncmp(s, "c", 1) == 0)
		return ((t_parse_type)c);
	if (ft_strncmp(s, "l", 1) == 0)
		return ((t_parse_type)l);
	ft_free(s);
	return (-1);
}

static void	assigned_func(void **func)
{
	func[(t_parse_type)R] = &parse_r;
	func[(t_parse_type)A] = &parse_a;
	func[(t_parse_type)c] = &parse_c;
	func[(t_parse_type)l] = &parse_l;
	func[(t_parse_type)sp] = &parse_sp;
	func[(t_parse_type)pl] = &parse_pl;
	func[(t_parse_type)sq] = &parse_sq;
	func[(t_parse_type)cy] = &parse_cy;
	func[(t_parse_type)tr] = &parse_tr;
	func[(t_parse_type)cu] = &parse_cu;
	func[(t_parse_type)co] = &parse_co;
}

void		parse_scene(int fd, t_parse *parse)
{
	char	*str;
	int		num[2];
	void	(*func[11])(t_parse*, char *);

	assigned_func((void**)func);
	num[0] = 1;
	while (num[0])
	{
		num[0] = get_next_line(fd, &str);
		num[1] = parse_type(str);
		if (num[1] != -1)
			func[num[1]](parse, str);
		ft_free(str);
	}
	if (parse->rx == 0 || parse->ry == 0)
		error_exit("couldn't find rendering size\n");
	if (parse->aratio == -1.0 || parse->acolor[0] == -1 ||
	parse->acolor[1] == -1 || parse->acolor[2] == -1)
		error_exit("couldn't find Ambient lightning\n");
	if (parse->camera == 0)
		error_exit("couldn't find any camera\n");
	if (DEBUG == 1)
		print_parse(parse);
}
