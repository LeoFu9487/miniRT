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
	if (temp->type == sp)
		func[sp](temp->ptr);
}

void	print_sp(void *lst)
{
	t_sphere	*temp;

	temp = (t_sphere*)lst;
	printf("sphere : \n coordinate : X %g Y : %g Z : %g\n diameter %g\n colors : \n R : %d\n G : %d\n B : %d\n", temp->coordinate[0], temp->coordinate[1], temp->coordinate[2], temp->diameter, temp->color[0], temp->color[1], temp->color[2]);
}
