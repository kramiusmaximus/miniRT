NAME = miniRT
SOURCES_DIRECTORY = srcs
SOURCES = $(shell find $(SOURCES_DIRECTORY) -name '*.c')
SOURCES_BONUS = $(shell)
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))
OBJECTS_BONUS = $(patsubst %.c, %.o, $(SOURCES))
INCLUDES_DIRECTORY = includes libft/includes mlx
HEADERS = $(shell find $(INCLUDES_DIRECTORY) -name '*.h')
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all:						${NAME}

$(NAME):					${OBJECTS}
							make -C libft
							make -C mlx
							$(CC) -Llibft -lft -framework OpenGL -framework AppKit $(OBJECTS) -o $(NAME) libmlx.dylib

test:						all
							./miniRT scenes/vistovka1.rt

%.o: 						%.c ${HEADERS}
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
