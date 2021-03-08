/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 19:55:01 by yfu               #+#    #+#             */
/*   Updated: 2021/03/08 15:12:31 by yfu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

typedef struct	s_bmp
{
	char			id[2];
	unsigned		size;
	unsigned		reserved;
	unsigned		offset;
	unsigned		headersize;
	unsigned		width;
	unsigned		height;
	unsigned short	planes;
	unsigned short	bitsperpixel;
	unsigned		compression;
	unsigned		imagesize;
	unsigned		xpixelspermeter;
	unsigned		ypixelspermeter;
	unsigned		totalcolors;
	unsigned		importantcolors;
}				t_bmp;

void			do_bmp(t_info *info, char *argv[2]);
void			create_file(char *file_name, t_camera *camera, t_info *info);
t_bmp			*set_bmp(t_info *info);
void			write_pixel(int fd, t_parse *parse, t_camera *camera);

#endif
