#include "../includes/minirt.h"

/*
Deal with '-' for r and a ?
*/

void	parse_r(t_parse *parse, char *str)
{
	if (parse->Rx || parse->Ry)
		error_exit("Define render size multiple times!\n");
	while (*str && ft_isdigit(*str) == 0)
		str++;
	parse->Rx = ft_atoi(str);
	while (*str && ft_isdigit(*str))
		str++;
	while (*str && ft_isdigit(*str) == 0)
		str++;
	parse->Ry = ft_atoi(str);
	if (parse->Rx <= 0 || parse->Ry <= 0)
		error_exit("couldn't find valid x and y rendering size\n");
}

void	parse_a(t_parse *parse, char *str)
{
	double	num;
	int		cnt;

	if (parse->Aratio != -1.0 || parse->Acolor[0] != -1 ||
	parse->Acolor[1] != -1 || parse->Acolor[2] != -1)
		error_exit("Define Ambient lightning multiple times\n");
	while (*str && ft_isdigit(*str) == 0)
		str++;
	if (*str == 0)
		error_exit("couldn't find valid Ambient lightning ratio\n");
	parse->Aratio = (double)(*(str++) - '0');
	if (*(str) == '.')
	{
		str++;
		num = (double)ft_atoi(str);
		while (num >= 1.0)
			num /= 10.0;
		(parse->Aratio) += num;
		while (*str && ft_isdigit(*str))
			str++;
	}
	cnt = -1;
	while (++cnt < 3)
	{
		while (*str && ft_isdigit(*str) == 0)
			str++;
		if (*str == 0)
			error_exit("couldn't find valid Ambient lightning color\n");
		parse->Acolor[cnt] = ft_atoi(str);
		while (*str && ft_isdigit(*str))
			str++;
		if (parse->Acolor[cnt] < 0 || parse->Acolor[cnt] > 255)
			error_exit("couldn't find valid Ambient lightning color\n");
	}
	if (parse->Aratio < 0.0 || parse->Aratio > 1.0)
		error_exit("couldn't find valid Ambient lightning ratio\n");
}

void	parse_c(t_parse *parse, char *str)
{
	(void)parse;
	printf("C!! %s\n", str);
}

void	parse_l(t_parse *parse, char *str)
{
	(void)parse;
	printf("L!! %s\n", str);
}
