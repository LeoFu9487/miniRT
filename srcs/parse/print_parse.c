#include "minirt.h"

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
	t_camera	*temp;

	temp = (t_camera*)lst;
	printf("camera %d : ", temp->num);
	printf("x : %g y : %g z : %g ", temp->coordinate[0],
	temp->coordinate[1], temp->coordinate[2]);
	printf("Vx : %g Vy : %g Vz : %g vof : %g\n", temp->orientation[0],
	temp->orientation[1], temp->orientation[2], temp->vof);
}

void	print_light(void *lst)
{
	static int	num = 0;
	t_light		*temp;

	temp = (t_light*)lst;
	printf("light %d x : %g y : %g z : %g ", num++, temp->coordinate[0],
	temp->coordinate[1], temp->coordinate[2]);
	printf("brightness : %g R : %d G : %d B : %d\n", temp->brightness,
	temp->color[0], temp->color[1], temp->color[2]);
}

void	print_objects(void *lst)
{
	void		(*func[10])(void *);
	t_objects	*temp;

	temp = (void*)lst;
	printf("objects%d : ", temp->num);
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
	printf("sphere : x : %g y : %g z : %g ", temp->coordinate[0],
	temp->coordinate[1], temp->coordinate[2]);
	printf("diameter : %g R : %d G : %d B : %d\n", temp->diameter,
	temp->color[0], temp->color[1], temp->color[2]);
}

void	print_pl(void *lst)
{
	t_plane		*temp;

	temp = (t_plane*)lst;
	printf("plane : x : %g y : %g z : %g ", temp->coordinate[0],
	temp->coordinate[1], temp->coordinate[2]);
	printf("Vx : %g Vy : %g Vz : %g ", temp->orientation[0],
	temp->orientation[1], temp->orientation[2]);
	printf("R : %d g : %d B : %d\n", temp->color[0],
	temp->color[1], temp->color[2]);
}

void	print_sq(void *lst)
{
	t_square	*temp;

	temp = (t_square*)lst;
	printf("square : x : %g y : %g z : %g ", temp->coordinate[0],
	temp->coordinate[1], temp->coordinate[2]);
	printf("Vx : %g Vy : %g Vz : %g ", temp->orientation[0],
	temp->orientation[1], temp->orientation[2]);
	printf("side_size : %g ", temp->side_size);
	printf("R : %d g : %d B : %d\n", temp->color[0],
	temp->color[1], temp->color[2]);
}

void	print_cy(void *lst)
{
	t_cylinder	*temp;

	temp = (t_cylinder*)lst;
	printf("cylinder : x : %g y : %g z : %g ", temp->coordinate[0],
	temp->coordinate[1], temp->coordinate[2]);
	printf("Vx : %g Vy : %g Vz : %g ", temp->orientation[0],
	temp->orientation[1], temp->orientation[2]);
	printf("diameter : %g height : %g ", temp->diameter, temp->height);
	printf("R : %d g : %d B : %d\n", temp->color[0],
	temp->color[1], temp->color[2]);
}

void	print_tr(void *lst)
{
	t_triangle	*temp;

	temp = (t_triangle*)lst;
	printf("triangle : Ax : %g Ay : %g Az : %g ", temp->point[0][0],
	temp->point[0][1], temp->point[0][2]);
	printf("triangle : Bx : %g By : %g Bz : %g ", temp->point[1][0],
	temp->point[1][1], temp->point[1][2]);
	printf("triangle : Cx : %g Cy : %g Cz : %g ", temp->point[2][0],
	temp->point[2][1], temp->point[2][2]);
	printf("R : %d G : %d B : %d\n", temp->color[0], temp->color[1],
	temp->color[2]);
}
