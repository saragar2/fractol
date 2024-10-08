
NAME	=	fractol

CFLAGS	=	-Wall -Wextra -Werror -g3 -fsanitize=address -O3 -fPIE 
STRUCT			= -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz



SRCS	=	color.c \
			image.c \
			julia.c \
			main.c \
			mandelbrot.c \
			utils.c

OBJS	=	${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(UTILS) $(OBJS)
	gcc $(CFLAGS) $(OBJS)  -o $(NAME) $(STRUCT) -I ./fractol.h

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re