/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 19:59:54 by yfu               #+#    #+#             */
/*   Updated: 2021/03/07 18:20:19 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# ifndef AMBIENT_LIGHT_INTENSITY
#  define AMBIENT_LIGHT_INTENSITY 0.05
# endif

/*
** L :
** x = 5t + 2
** y = 6t + 1
** z = 7y + 3
** => x[0] = 5, x[1] = 2 ...
*/

typedef struct	s_line
{
	double	x[2];
	double	y[2];
	double	z[2];
}				t_line;

typedef struct	s_parse
{
	int		rx;
	int		ry;
	double	aratio;
	int		acolor[3];
	t_list	*camera;
	t_list	*cur_camera;
	t_list	*light;
	t_list	*objects;
	t_list	*flashlight;
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
	tr,
	cu,
	co,
	py,
	fl
}				t_parse_type;

typedef struct	s_camera
{
	int		num;
	double	coordinate[3];
	double	orientation[3];
	double	vof;
	double	distance_to_screen;
	void	*img_ptr[17];
	int		*pixel[17];
	int		*bits_per_pixel[17];
	int		*size_line[17];
	int		*endian[17];
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
	int				num;
	void			*ptr;
}				t_objects;

typedef struct	s_sphere
{
	double			coordinate[3];
	double			diameter;
	int				color[3];
}				t_sphere;

typedef struct	s_plane
{
	double			coordinate[3];
	double			orientation[3];
	int				color[3];
}				t_plane;

typedef struct	s_square
{
	double			coordinate[3];
	double			orientation[3];
	double			start_point[3];
	double			*vector[2];
	double			side_size;
	int				color[3];
}				t_square;

typedef struct	s_cylinder
{
	double			coordinate[3];
	double			orientation[3];
	double			diameter;
	double			height;
	int				color[3];
	t_line			*middle_line;
	double			*end_point[2];
}				t_cylinder;

typedef struct	s_triangle
{
	double			point[3][3];
	double			*orientation;
	double			*vector[2];
	int				color[3];
}				t_triangle;

typedef struct	s_cube
{
	double		coordinate[3];
	double		side_size;
	int			color[3];
	t_square	*square[6];
}				t_cube;

typedef struct	s_cone
{
	double			coordinate[3];
	double			orientation[3];
	double			diameter;
	double			height;
	int				color[3];
	double			*end_point[2];
}				t_cone;

typedef struct	s_pyramid
{
	t_square		*square;
	t_triangle		*triangle[4];
}				t_pyramid;

typedef struct	s_flashlight
{
	double	coordinate[3];
	double	orientation[3];
	double	brightness;
	double	diameter;
	int		color[3];
}				t_flashlight;

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
void			parse_cu(t_parse *parse, char *str);
void			parse_co(t_parse *parse, char *str);
void			parse_py(t_parse *parse, char *str);
void			parse_fl(t_parse *parse, char *str);
t_parse			*init_parse(void);
t_camera		*init_camera(void);
t_light			*init_light(void);
t_objects		*init_objects(t_parse_type	type, void	*add);
t_sphere		*init_sphere(void);
t_plane			*init_plane(void);
t_square		*init_square(void);
t_cylinder		*init_cylinder(void);
t_triangle		*init_triangle(void);
t_cube			*init_cube(void);
t_cone			*init_cone(void);
t_pyramid		*init_pyramid(void);
t_flashlight	*init_flashlight(void);
void			compose_cube(t_cube *cube);
void			cone_coef(double *coef, double *alpha, t_line *l, t_cone *cone);
void			cylinder_coef(double *coef, double *alpha, t_line *l,
t_cylinder *cylinder);
void			assign_v(double v[3][3], t_line *l);

#endif
