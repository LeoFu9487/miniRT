#include "../includes/minirt.h"

int     cnt = 0;
void    *mlx_ptr;
void    *win_ptr;

int     close_program(void *param);
int     deal_key(int key, void *param)
{
	(void)param;
        int color = key * 512 * 512 + key * 512 + key;
        int x = cnt % 5, y = cnt / 5;
        for(int i = 0 ; i < 100 ; i++)
          for(int j = 0 ; j < 100 ; j++)
           mlx_pixel_put(mlx_ptr, win_ptr, x * 100 + i, y * 100 + j, color);
        cnt++;
        cnt %= 25;
        if (key == ESC)
                close_program((void*)0);
        return (0);
}

int     deal_mouse(int button, int x, int y, void *param)
{
	(void)param;
	(void)button;
        x /= 100;
        y /= 100;
        int color = 012345;
        for(int i = 0 ; i < 100 ; i++)
          for(int j = 0 ; j < 100 ; j++)
           mlx_pixel_put(mlx_ptr, win_ptr, x * 100 + i, y * 100 + j, color);
	return (1);
}

int     close_program(void *param)
{
	(void)param;
        printf("Program is closed ! \n");
	exit(EXIT_SUCCESS);
	return (1);
}

int main()
{
mlx_ptr = mlx_init();
        win_ptr = mlx_new_window(mlx_ptr, 500, 500, "Hello World !");
        for(int i = 0 ; i < 100 ; i++)
          for(int j = 0 ; j < 100 ; j++)
           mlx_pixel_put(mlx_ptr, win_ptr, i, j, 0100);
        mlx_key_hook(win_ptr, deal_key, (void*)0);
        mlx_mouse_hook(win_ptr, deal_mouse, (void*)0);
        mlx_hook(win_ptr, 17, 131072, close_program, 0);
        mlx_loop(mlx_ptr);
}
