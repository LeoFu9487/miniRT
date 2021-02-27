#include "minirt.h"

void	create_file(char *file_name, t_camera *camera, t_info *info)
{
	int	fd;

	if ((fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) < 0)
		error_exit("fail to create file\n");
	bmp_header(camera, fd);
}

void	bmp_header(t_info *info, int fd)
{
	
}

void	do_bmp(t_info *info, char *file_name)
{
	char		*str[2];
	int			len;
	t_camera	*camera;

	str[0] = file_name;
	while (*(str[0]))
		if (*(str[0]++) == '/')
			file_name = str[0];
	len = ft_strlen(file_name);
	len -= 3;
	file_name[len] = '\0';
	while (info->parse->camera)
	{
		camera = info->parse->camera->content;
		str[1] = ft_itoa(camera->num);
		if (!(str[0] = ft_malloc(len + 13 + ft_strlen(str[1]), sizeof(char))))
			error_exit("do_bmp\n");
		str[0][0] = '\0';
		ft_strcat(str[0], "images/");
		ft_strcat(str[0], file_name);
		ft_strcat(str[0], "_");
		ft_strcat(str[0], str[1]);
		ft_strcat(str[0], ".bmp");
		create_file(str[0], camera, info);
		info->parse->camera = info->parse->camera->next;
	}
	exit(EXIT_SUCCESS);
}
