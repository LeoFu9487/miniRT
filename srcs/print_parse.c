#include "../includes/minirt.h"

void	print_parse(t_parse *parse)
{
	printf("Rx : %d Ry : %d\n", parse->rx, parse->ry);
	printf("Aratio : %g Acolors : %d %d %d\n",
	parse->aratio, parse->acolor[0], parse->acolor[1], parse->acolor[2]);
	ft_lstiter(parse->camera, print_camera);
	ft_lstiter(parse->light, print_light);
	ft_lstiter(parse->objects, print_objects);
}

void	print_camera(void *lst)
{
	t_camera	*temp = (t_camera*)lst;

	printf("camera : \n coordinate : X : %g Y : %g Z : %g\n orientation : X : %g Y : %g Z : %g\n vof : %g\n", temp->coordinate[0], temp->coordinate[1], temp->coordinate[2], temp->orientation[0], temp->orientation[1], temp->orientation[2], temp->vof);
}

void	print_light(void *lst)
{
	t_light		*temp = (t_light*)lst;

	printf("light : \n coordinate : X %g Y : %g Z : %g\n brightness %g\n colors : \n R : %d\n G : %d\n B : %d\n", temp->coordinate[0], temp->coordinate[1], temp->coordinate[2], temp->brightness, temp->color[0], temp->color[1], temp->color[2]);
}

void	print_objects(void *lst)
{
	void	(*func[10])(void *);

	t_objects	*temp = (void*)lst;
	func[sp] = print_sp;
	func[pl] = print_pl;
	func[sq] = print_sq;
	func[cy] = print_cy;
	func[tr] = print_tr;
	func[temp->type](temp->ptr);
}

void	print_sp(void *lst)
{
	t_sphere	*temp;

	temp = (t_sphere*)lst;
	printf("sphere : \n coordinate : X %g Y : %g Z : %g\n diameter %g\n colors : R : %d G : %d B : %d\n", temp->coordinate[0], temp->coordinate[1], temp->coordinate[2], temp->diameter, temp->color[0], temp->color[1], temp->color[2]);
}

void	print_pl(void *lst)
{
	t_plane		*temp;

	temp = (t_plane*)lst;
	printf("plane : \n coordinate : X %g Y : %g Z : %g\n orientation : X %g Y %g Z %g\n colors : R : %d G : %d B : %d\n", temp->coordinate[0], temp->coordinate[1], temp->coordinate[2], temp->orientation[0], temp->orientation[1], temp->orientation[2], temp->color[0], temp->color[1], temp->color[2]);
}

void	print_sq(void *lst)
{
	t_square	*temp;

	temp = (t_square*)lst;
	printf("square : \n coordinate : X %g Y : %g Z : %g\n orientation : X %g Y %g Z %g\n side_size : %g\n colors : R %d G : %d B : %d\n", temp->coordinate[0], temp->coordinate[1], temp->coordinate[2], temp->orientation[0], temp->orientation[1], temp->orientation[2], temp->side_size, temp->color[0], temp->color[1], temp->color[2]);
}

void	print_cy(void *lst)
{
	t_cylinder	*temp;

	temp = (t_cylinder*)lst;
	printf("cylinder : \n coordinate : X %g Y : %g Z : %g\n orientation : X %g Y %g Z %g\n diameter : %g\nheight : %g\n colors : R %d G %d B %d\n", temp->coordinate[0], temp->coordinate[1], temp->coordinate[2], temp->orientation[0], temp->orientation[1], temp->orientation[2], temp->diameter, temp->height, temp->color[0], temp->color[1], temp->color[2]);
}

void	print_tr(void *lst)
{
	t_triangle	*temp;

	temp = (t_triangle*)lst;
	printf("triangle : point A : x %g y %g z %g\n point B : x %g y %g z %g\n point C : x %g y %g z %g\n color : R %d G %d B %d\n", temp->point[0][0], temp->point[0][1], temp->point[0][2], temp->point[1][0], temp->point[1][1], temp->point[1][2], temp->point[2][0], temp->point[2][1], temp->point[2][2], temp->color[0], temp->color[1], temp->color[2]);
}