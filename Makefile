NAME = miniRT
SOURCES_DIRECTORY = srcs
SOURCES = $(shell find $(SOURCES_DIRECTORY) -name '*.c')
SOURCES_BONUS = $(shell)
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))
OBJECTS_BONUS = $(patsubst %.c, %.o, $(SOURCES))
INCLUDES_DIRECTORY = includes libft/includes mlx
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all:						${NAME}

$(NAME):					${OBJECTS}
							make -C libft
							make -C mlx
							mv mlx/libmlx.dylib .
							$(CC) -Llibft -lft -libmlx.dylib -framework Metal -framework OpenGL -framework AppKit $(OBJECTS) -o $(NAME)

test:						all
							./miniRT scenes/infinity.rt

%.o: 						%.c
							$(CC) $(CFLAGS) $(addprefix -I, $(INCLUDES_DIRECTORY)) -c -o $@ $<

clean:
							rm -f $(OBJECTS)
							make -C libft clean
							make -C mlx clean

fclean:						clean
							rm -f $(NAME)

re:							fclean all

bonus:					${OBJECTS} ${OBJECTS_BONUS}
							make -C libft
							make -C mlx
