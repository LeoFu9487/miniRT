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
double			two_points_distance(double *a, double *b);
double			*two_points_vector(double *start_point, double *end_point);
double			*reflection_color(int *color, t_light *light, double new_brightness);
t_line			*two_points_line(double	*p1, double	*p2);
int				have_intersection(t_list *lst, t_line *line);
int				have_intersection_sp(t_line *l, void *ptr);
int				have_intersection_pl(t_line *l, void *ptr);
int				have_intersection_sq(t_line *l, void *ptr);
int				have_intersection_cy(t_line *l, void *ptr);
int				have_intersection_tr(t_line *l, void *ptr);
void			intersect_color(t_intersect *it, t_parse *parse);
int				quadratic_equation(double *coef, double *answer);
t_intersect		*init_intersect(t_parse *parse);
void			find_intersect(t_intersect *is, t_line *l, t_list *obj);
void			modify_length(double *vector, double length);
t_line			*new_line(t_camera *camera, double *u, double *v, double *position);
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
double			linear_equation(double *coef, t_line *line);
void			linear_equations(double *u, double *v, double *w, double *ans);
double			det(double **mat, int size);
double			*make_point(double a, double b, double c);
double			double_abs(double a);

#endif
