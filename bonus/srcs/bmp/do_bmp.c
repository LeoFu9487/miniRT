/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_bmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 22:35:34 by yfu               #+#    #+#             */
/*   Updated: 2021/03/09 14:17:30 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		create_file(char *file_name, t_camera *camera, t_info *info)
{
	int				fd;
	static t_bmp	*bmp;

	if ((fd = open(file_name, O_RDWR | O_CREAT |
	O_TRUNC, S_IRUSR | S_IWUSR)) < 0)
		error_exit("fail to create file\n");
	if (!bmp)
		bmp = set_bmp(info);
	write(fd, &(bmp->id), 2);
	write(fd, &(bmp->size), 4);
	write(fd, &(bmp->reserved), 4);
	write(fd, &(bmp->offset), 4);
	write(fd, &(bmp->headersize), 4);
	write(fd, &(bmp->width), 4);
	write(fd, &(bmp->height), 4);
	write(fd, &(bmp->planes), 2);
	write(fd, &(bmp->bitsperpixel), 2);
	write(fd, &(bmp->compression), 4);
	write(fd, &(bmp->imagesize), 4);
	write(fd, &(bmp->xpixelspermeter), 4);
	write(fd, &(bmp->ypixelspermeter), 4);
	write(fd, &(bmp->totalcolors), 4);
	write(fd, &(bmp->importantcolors), 4);
	write_pixel(fd, info->parse, camera);
	close(fd);
}

t_bmp		*set_bmp(t_info *info)
{
	t_bmp	*bmp;

	if (!(bmp = ft_malloc(1, sizeof(t_bmp))))
		error_exit("set_bmp\n");
	bmp->id[0] = 'B';
	bmp->id[1] = 'M';
	bmp->size = info->parse->rx * info->parse->ry * 4 + 54;
	bmp->reserved = 0;
	bmp->offset = 54;
	bmp->headersize = 40;
	bmp->width = info->parse->rx;
	bmp->height = info->parse->ry;
	bmp->planes = 1;
	bmp->bitsperpixel = 32;
	bmp->compression = 0;
	bmp->imagesize = 0;
	bmp->xpixelspermeter = 0;
	bmp->ypixelspermeter = 0;
	bmp->totalcolors = 0;
	bmp->importantcolors = 0;
	return (bmp);
}

void		write_pixel(int fd, t_parse *parse, t_camera *camera)
{
	int		ct[3];
	char	str[4];

	ct[0] = parse->ry;
	while (--ct[0] >= 0)
	{
		ct[1] = -1;
		while (++ct[1] < parse->rx)
		{
			str[3] = (camera->pixel[0][ct[0] * parse->rx + ct[1]] >> 24) &
			((1 << 8) - 1);
			str[2] = (camera->pixel[0][ct[0] * parse->rx + ct[1]] >> 16) &
			((1 << 8) - 1);
			str[1] = (camera->pixel[0][ct[0] * parse->rx + ct[1]] >> 8) &
			((1 << 8) - 1);
			str[0] = (camera->pixel[0][ct[0] * parse->rx + ct[1]] >> 0) &
			((1 << 8) - 1);
			write(fd, str, 4);
		}
	}
}

static void	get_file_name(char *str[3], char *file_name, t_info *info, int len)
{
	t_camera	*camera;

	camera = info->parse->camera->content;
	str[1] = ft_itoa(camera->num);
	if (!(str[0] = ft_malloc(len + 13 + ft_strlen(str[1]), sizeof(char))))
		error_exit("do_bmp\n");
	str[0][0] = '\0';
	ft_strcat(str[0], str[2]);
	ft_strcat(str[0], "images/");
	ft_strcat(str[0], file_name);
	ft_strcat(str[0], "_");
	ft_strcat(str[0], str[1]);
	ft_strcat(str[0], ".bmp");
	create_file(str[0], camera, info);
	info->parse->camera = info->parse->camera->next;
	ft_free(str[0]);
	ft_free(str[1]);
}

void		do_bmp(t_info *info, char *argv[2])
{
	char		*str[3];
	char		*file_name;
	int			len;

	file_name = argv[1];
	str[0] = file_name;
	while (*(str[0]))
		if (*(str[0]++) == '/')
			file_name = str[0];
	len = ft_strlen(argv[0]) - 12;
	str[2] = argv[0];
	str[2][len] = '\0';
	len += ft_strlen(file_name) - 3;
	file_name[ft_strlen(file_name) - 3] = '\0';
	while (info->parse->camera)
		get_file_name(str, file_name, info, len);
	ft_putstr_fd("check the repository \"images\" to ", 2);
	ft_putendl_fd("find the pictures in bmp format", 2);
	exit(EXIT_SUCCESS);
}
