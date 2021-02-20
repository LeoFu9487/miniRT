#ifndef MATH2_H
# define MATH2_H

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

typedef struct	s_intersect
{
	int		intersect;
	double	coordinate[3];
	int		color[3];
}				t_intersect;

t_intersect		*init_intersect(void);
void			find_intersect(t_intersect *is, t_line *l, t_list *obj);
t_line			*new_line(t_camera *camera, double *u, double *v, int *position);
double			*cross(double *v1, double *v2);
double			dot(double *v1, double *v2);
double			len(double *v);
double			cos_vector(double *v1, double *v2);
double			*add_vector(double *v1, double *v2);

#endif