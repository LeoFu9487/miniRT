MACOS_MINILIBX =  minilibx_mms_20200219

MACOS_FLAGS =  -I $(MACOS_MINILIBX) -L $(MACOS_MINILIBX) -lmlx -framework OpenGL -framework AppKit

UNAME = $(shell uname)

LINUX_MINILIBX = minilibx-linux

LINUX_FLAGS = -I $(LINUX_MINILIBX) -L $(LINUX_MINILIBX) -lmlx -lm -lX11 -lXext -lpthread

ifeq ($(UNAME), Darwin)
	CFLAGS = libmlx.dylib
endif

ifeq ($(UNAME), linux)
	CFALGS = $(LINUX_FLAGS)
endif

go :
	gcc try.c $(CFLAGS) -o program

