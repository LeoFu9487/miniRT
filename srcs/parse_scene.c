#include "../includes/minirt.h"

t_parse		*init_parse(void)
{
	t_parse	*parse;

	parse = ft_malloc(1, sizeof(t_parse));
	parse->Rx = 0;
	parse->Ry = 0;
	parse->obj = NULL;
	parse->light = NULL;
	parse->camera = NULL;
	parse->Aratio = -1.0;
	parse->Acolor[0] = -1;
	parse->Acolor[1] = -1;
	parse->Acolor[2] = -1;
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
	func[0] = &parse_r;
	func[1] = &parse_a;
	func[2] = &parse_c;
	func[3] = &parse_l;
	func[4] = &parse_sp;
	func[5] = &parse_pl;
	func[6] = &parse_sq;
	func[7] = &parse_cy;
	func[8] = &parse_tr;
}

void		parse_scene(int fd, t_parse *parse)
{
	char	*str;
	int		num[2];
	void	(*func[9])(t_parse*, char *);

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
}
