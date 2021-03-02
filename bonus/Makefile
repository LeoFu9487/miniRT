#take the -fsanitize=address away ?
#if uname == darwin ? 
#change minilibx
# if change minilibx, change minirt.h
# take away DEBUG_FLAGS

NAME = miniRT_bonus

UNAME = $(shell uname)

HEAD = includes

LIB = ../lib/

CC = gcc

FLAGS = -Wall -Wextra -Werror -fsanitize=address -I $(HEAD)

LIBFLAGS = -L $(LIB)libft -lft -I $(LIB)libft

MACOS_MACRO = -D MACOS

LINUX_MACRO = -D LINUX

MACOS_MINILIBX = $(addprefix $(LIB), minilibx_opengl_20191021)

LINUX_MINILIBX = $(addprefix $(LIB), minilibx-linux)

MACOS_FLAGS =  -I $(MACOS_MINILIBX) -L $(MACOS_MINILIBX) -lmlx -framework OpenGL -framework AppKit

LINUX_FLAGS = -I $(LINUX_MINILIBX) -L $(LINUX_MINILIBX) -lmlx -lmlx_Linux -lm -lX11 -lXext -lpthread

ifeq ($(UNAME),Darwin)
	LIBFLAGS += $(MACOS_FLAGS)
	CFLAGS = $(MACOS_MACRO) $(LIBFLAGS) $(DEBUG_FLAGS) $(FLAGS)
	MINILIBX = $(MACOS_MINILIBX)
endif

ifeq ($(UNAME),Linux)
	LIBFLAGS += $(LINUX_FLAGS)
	CFLAGS += $(LINUX_MACRO) $(LIBFLAGS) $(DEBUG_FLAGS) $(FLAGS)
	MINILIBX = $(LINUX_MINILIBX)
endif


FILES = main.c	error.c

OBJECT_FILES = 	camera.c	light.c\
	objects.c	sphere.c	plane.c		square.c\
	cylinder.c	triangle.c	cube.c		cone.c\
	pyramid.c	flashlight.c

PARSE_FILES = parse_scene.c	parse_func_0.c	parse_func_1.c	print_parse.c

PUT_FILES = open_window.c	put_screen.c	color.c	load_images.c

MATH_FILES = vector.c	math.c	utils.c	utils2.c\
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

$(NAME):	$(OBJS)
		make -C $(LIB)libft
		make -C $(MINILIBX)
		$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

all : $(NAME)

clean :
	make clean -C $(LIB)libft
	make clean -C $(MINILIBX)
	rm -rf $(OBJS)

fclean :
	make fclean -C $(LIB)libft
	make clean -C $(MINILIBX)
	rm -rf $(OBJS)
	rm -rf $(NAME)
	
re :	fclean all

.PHONY : all clean fclean re
