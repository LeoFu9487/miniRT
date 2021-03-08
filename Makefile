#take the -fsanitize=address away ?
#if uname == darwin ? 
#change minilibx
# if change minilibx, change minirt.h
# take away DEBUG_FLAGS

NAME = miniRT

NAME_BONUS = miniRT_bonus

HEAD = includes

LIB = lib/

CC = gcc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -I $(HEAD)

UNAME = $(shell uname)

FILES = main.c	error.c

OBJECT_FILES = 	camera.c	light.c\
	objects.c	sphere.c	plane.c		square.c	square_2.c\
	cylinder.c	cylinder_2.c	cylinder_3.c	triangle.c	triangle_2.c	cube.c	cube_2.c	cone.c	cone_2.c\
	pyramid.c	flashlight.c

PARSE_FILES = parse_scene.c	parse_r.c	parse_a.c	parse_c.c\
	      parse_l.c	parse_sp.c	parse_pl.c	parse_sq.c\
	      parse_cy.c	parse_tr.c	parse_cu.c	parse_co.c\
	      parse_py.c	parse_fl.c

PUT_FILES = open_window.c	put_screen.c	put_screen_2.c\
	color.c	load_images.c	open_window_2.c

MATH_FILES = vector.c	math.c	utils.c	utils1.c	utils2.c\
	     vector2.c	utils3.c

BMP_FILES = do_bmp.c

OBJECT_DIR = object/

PARSE_DIR = parse/

SRCS_DIR = srcs/

PUT_DIR = put/

MATH_DIR = math/

BMP_DIR = bmp/

FILES += $(addprefix $(OBJECT_DIR), $(OBJECT_FILES))

FILES += $(addprefix $(PUT_DIR), $(PUT_FILES))

FILES += $(addprefix $(PARSE_DIR), $(PARSE_FILES))

FILES += $(addprefix $(MATH_DIR), $(MATH_FILES))

FILES += $(addprefix $(BMP_DIR), $(BMP_FILES))

SRCS = $(addprefix $(SRCS_DIR), $(FILES))

OBJS = $(SRCS:.c=.o)

LIBFLAGS = -L $(LIB)libft -lft

MACOS_MACRO = -D MACOS

LINUX_MACRO = -D LINUX

MACOS_MINILIBX = $(addprefix $(LIB), minilibx_opengl_20191021)

LINUX_MINILIBX = $(addprefix $(LIB), minilibx-linux)

MACOS_FLAGS =  -I $(MACOS_MINILIBX) -L $(MACOS_MINILIBX) -lmlx -framework OpenGL -framework AppKit

LINUX_FLAGS = -I $(LINUX_MINILIBX) -L $(LINUX_MINILIBX) -lmlx -lmlx_Linux -lm -lX11 -lXext -lpthread

CFLAGS += $(DEBUG_FLAGS)

ifeq ($(UNAME),Darwin)
	LIBFLAGS += $(MACOS_FLAGS)
	CFLAGS += $(MACOS_MACRO)
	MINILIBX = $(MACOS_MINILIBX)
endif

ifeq ($(UNAME),Linux)
	LIBFLAGS += $(LINUX_FLAGS)
	CFLAGS += $(LINUX_MACRO)
	MINILIBX = $(LINUX_MINILIBX)
endif

$(NAME):	$(OBJS)
		make -C $(LIB)libft
		make -C $(MINILIBX)
		$(CC) $(OBJS) $(CFLAGS) $(LIBFLAGS) -o $(NAME)

$(NAME_BONUS):
	make -C bonus
	cp bonus/$(NAME_BONUS) .

all : $(NAME)

bonus :	$(NAME_BONUS)

clean :
	make clean -C $(LIB)libft
	make clean -C bonus
	make clean -C $(MINILIBX)
	rm -rf $(OBJS)
	
fclean :
	make fclean -C $(LIB)libft
	make fclean -C bonus
	make clean -C $(MINILIBX)
	rm -rf $(NAME_BONUS)
	rm -rf $(OBJS)
	rm -rf $(NAME)
	
re :	fclean all

norm :
	norminette srcs/*.c includes/*.h
	$(MAKE) norm -C lib/libft/

.PHONY : all clean fclean re bonus debug norm
