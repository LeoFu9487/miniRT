#ifndef PARSE_H
# define PARSE_H

typedef struct	s_parse
{
	int		rx;
	int		ry;
	double	aratio;
	int		acolor[3];
	t_list	*camera;
	t_list	*light;
	t_list	*objects;
}				t_parse;

typedef enum	e_parse_type
{
	R = 0,
	A,
	c,
	l,
	sp,
	pl,
	sq,
	cy,
	tr
}				t_parse_type;

typedef struct	s_camera
{
	double	coordinate[3];
	double	orientation[3];
	double	vof;
}				t_camera;

typedef struct	s_light
{
	double	coordinate[3];
	double	brightness;
	int		color[3];
}				t_light;

typedef struct	s_objects
{
	t_parse_type	type;
	void			*ptr;
}				t_objects;

typedef struct	s_sphere
{
	double			coordinate[3];
	double			diameter;
	int				color[3];
}				t_sphere;

void			parse_scene(int fd, t_parse *parse);
void			parse_r(t_parse *parse, char *str);
void			parse_a(t_parse *parse, char *str);
void			parse_c(t_parse *parse, char *str);
void			parse_l(t_parse *parse, char *str);
void			parse_sp(t_parse *parse, char *str);
void			parse_pl(t_parse *parse, char *str);
void			parse_sq(t_parse *parse, char *str);
void			parse_cy(t_parse *parse, char *str);
void			parse_tr(t_parse *parse, char *str);
t_parse			*init_parse(void);
t_camera		*init_camera(void);
t_light			*init_light(void);
t_objects		*init_objects(t_parse_type	type, void	*add);
t_sphere		*init_sphere(void);
void			print_parse(t_parse *parse);
void			print_camera(void *lst);
void			print_light(void *lst);
void			print_objects(void *lst);
void			print_sp(void *lst);

#endif
