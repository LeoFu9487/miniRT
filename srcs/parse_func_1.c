#include "../includes/minirt.h"

void	parse_sp(t_parse *parse, char *str)
{
	t_sphere	*sphere;

	sphere = init_sphere();
	ft_lstadd_front(&(parse->objects), ft_lstnew(init_objects(sp, sphere)));
	(void)str;

}

void	parse_pl(t_parse *parse, char *str)
{
	(void)parse;
	printf("PL!! %s\n", str);
}

void	parse_sq(t_parse *parse, char *str)
{
	(void)parse;
	printf("SQ!! %s\n", str);
}

void	parse_cy(t_parse *parse, char *str)
{
	(void)parse;
	printf("CY!! %s\n", str);
}

void	parse_tr(t_parse *parse, char *str)
{
	(void)parse;
	printf("TR!! %s\n", str);
}
