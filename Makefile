
NAME = fractol.a

SOURCES = main.c julia.c color.c image.c mandelbrot.c utils.c

OBJECTS = $(SOURCES:.c=.o)

CFLAGS := -Wall -Wextra -Werror -Imlx
REMOVE = rm -f
CC := cc

all: $(NAME)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

$(NAME): $(OBJECTS) mlx/libmlx.a
	$(CC) $(OBJECTS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

mlx/libmlx.a:
	make -C mlx/

run:
	./test

clean:
	$(REMOVE) $(OBJECTS)
	make -C mlx/ clean

fclean: clean
	$(REMOVE) $(NAME)

re: fclean all