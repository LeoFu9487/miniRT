#ifndef BMP_H
# define BMP_H

typedef struct	t_bmp
{
	
}				s_bmp;

void	do_bmp(t_info *info, char *file_name);
void	create_file(char *file_name, t_camera *camera, t_info *info);
void	bmp_header(t_info *info, inf fd);

#endif