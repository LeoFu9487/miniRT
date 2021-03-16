/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math2.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 19:55:48 by yfu               #+#    #+#             */
/*   Updated: 2021/03/07 18:31:35 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH2_H
# define MATH2_H
# define LEN_UNIT 500.0

typedef struct	s_intersect
{
	int		intersect;
	double	coordinate[3];
	int		color[3];
	double	dist;
	int		obj_num;
}				t_intersect;

double			*normal_vector_sp(double *point, void *ptr);
double			*normal_vector_pl(double *point, void *ptr);
double			*normal_vector_tr(double *point, void *ptr);
double			*normal_vector_sq(double *point, void *ptr);
double			*normal_vector_cy(double *point, void *ptr);
double			*normal_vector_cu(double *point, void *ptr);
double			*normal_vector_co(double *point, void *ptr);
double			*normal_vector_py(double *point, void *ptr);
double			two_points_distance(double *a, double *b);
double			*two_points_vector(double *start_point, double *end_point);
double			*reflection_color(int *color, t_light *light, double b);
double			*flashlight_reflection(int *color, t_flashlight *f, double b);
t_line			*two_points_line(double	*p1, double	*p2);
int				have_intersection(t_list *lst, t_line *line);
int				have_intersection_sp(t_line *l, void *ptr);
int				have_intersection_pl(t_line *l, void *ptr);
int				have_intersection_sq(t_line *l, void *ptr);
int				have_intersection_cy(t_line *l, void *ptr);
int				have_intersection_tr(t_line *l, void *ptr);
int				have_intersection_cu(t_line *l, void *ptr);
int				have_intersection_co(t_line *l, void *ptr);
int				have_intersection_py(t_line *l, void *ptr);
void			intersect_color(t_intersect *it, t_parse *parse);
int				quadratic_equation(double *coef, double *answer);
t_intersect		*init_intersect(t_parse *parse);
void			find_intersect(t_intersect *is, t_line *l, t_list *obj);
void			modify_length(double *vector, double length);
t_line			*new_line(t_camera *camera, double *u, double *v, double *p);
double			*cross(double *v1, double *v2);
double			dot(double *v1, double *v2);
double			len(double *v);
double			cos_vector(double *v1, double *v2);
double			*add_vector(double *v1, double *v2);
void			intersect_sp(t_intersect *is, t_line *l, void *ptr, int num);
void			intersect_pl(t_intersect *is, t_line *l, void *ptr, int num);
void			intersect_sq(t_intersect *is, t_line *l, void *ptr, int num);
void			intersect_cy(t_intersect *is, t_line *l, void *ptr, int num);
void			intersect_tr(t_intersect *is, t_line *l, void *ptr, int num);
void			intersect_cu(t_intersect *is, t_line *l, void *ptr, int num);
void			intersect_co(t_intersect *is, t_line *l, void *ptr, int num);
void			intersect_py(t_intersect *is, t_line *l, void *ptr, int num);
double			linear_equation(double *coef, t_line *line);
void			linear_equations(double *u, double *v, double *w, double *ans);
double			det(double **mat, int size);
double			*make_point(double a, double b, double c);
double			double_abs(double a);
void			copy_vector(double *target, double *srcs);
void			copy_color(int *target, int *srcs);
int				in_flashlight_range(double *point, t_flashlight *flashlight);
t_intersect		*get_intersect(t_info *info, int *pixel, double *u, double *v);
double			flashlight_new_brightness(t_objects *obj, t_intersect *it,
				t_flashlight *flashlight, t_parse *parse);
double			get_new_brightness(t_objects *obj, t_intersect *it,
				t_light *light, t_parse *parse);

#endif
