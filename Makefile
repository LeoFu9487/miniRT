#take the -fsanitize=address away ?
#if uname == darwin ? 
#change minilibx
# if change minilibx, change minirt.h
# take away DEBUG_FLAGS

NAME = miniRT

HEAD = includes

LIB = lib/

CC = gcc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -I $(HEAD)

UNAME = $(shell uname)

FILES = main.c	error.c	camera.c	light.c\
	objects.c	sphere.c	plane.c		square.c\
	cylinder.c	triangle.c

PARSE_FILES = parse_scene.c	parse_func_0.c	parse_func_1.c	print_parse.c

PARSE_SRCS = parse/

SRCS_DIR = srcs/

FILES += $(addprefix $(PARSE_SRCS), $(PARSE_FILES))

SRCS = $(addprefix $(SRCS_DIR), $(FILES))

OBJS = $(SRCS:.c=.o)

LIBFLAGS = -L $(LIB)libft -lft

MACOS_MACRO = -D MACOS

LINUX_MACRO = -D LINUX

MACOS_MINILIBX = $(addprefix $(LIB), minilibx_opengl_20191021)

LINUX_MINILIBX = $(addprefix $(LIB), minilibx-linux)

MACOS_FLAGS =  -I $(MACOS_MINILIBX) -L $(MACOS_MINILIBX) -lmlx -framework OpenGL -framework AppKit

LINUX_FLAGS = -I $(LINUX_MINILIBX) -L $(LINUX_MINILIBX) -lmlx -lm -lX11 -lXext -lpthread

CFLAGS += $(DEBUG_FLAGS)

ifeq ($(UNAME),Darwin)
	LIBFLAGS += $(MACOS_FLAGS)
	CFLAGS += $(MACOS_MACRO)
endif

ifeq ($(UNAME),Linux)
	LIBFLAGS += $(LINUX_FLAGS)
	CFLAGS += $(LINUX_MACRO)
endif

$(NAME):	$(OBJS)
		make -C $(LIB)libft
		$(CC) $(CFLAGS) $(OBJS) $(LIBFLAGS) -o $(NAME)

all : $(NAME)

bonus : $(NAME)

clean :
	make clean -C $(LIB)libft
	rm -rf $(OBJS)

fclean :
	make fclean -C $(LIB)libft
	rm -rf $(OBJS)
	rm -rf $(NAME)
	
re :	fclean all

debug :
	$(MAKE) fclean
	$(MAKE) DEBUG_FLAGS=-D\ DEBUG=1
	$(MAKE) clean

norm :
	norminette srcs/*.c includes/*.h
	$(MAKE) norm -C lib/libft/

git :
	git add srcs/*.c includes/*.h Makefile lib/*/*.c lib/*/*.h lib/*/Makefile tests/*
	git commit -m "$(message)"

.PHONY : all clean fclean re norm
