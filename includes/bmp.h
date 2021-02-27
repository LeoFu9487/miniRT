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

void	do_bmp(t_info *info, char *file_name);
void	create_file(char *file_name, t_camera *camera, t_info *info);
t_bmp	*set_bmp(t_info *info);
void	write_bmp(t_bmp *bmp, int fd);
void	write_pixel(int fd, t_parse *parse, t_camera *camera);

#endif