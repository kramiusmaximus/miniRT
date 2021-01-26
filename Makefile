NAME = miniRT
SOURCES_DIRECTORY = srcs
SOURCES = $(shell find $(SOURCES_DIRECTORY) -name '*.c')
SOURCES_LIBFT = $(shell find libft -name '*.c')
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))
OBJECTS_LIBFT = $(patsubst %.c, %.o, $(SOURCES_LIBFT))
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all:						${NAME}

$(NAME):					${OBJECTS}
							$(CC) -Lmlx -lmlx -framework OpenGL -framework AppKit $(OBJECTS) -o $(NAME)

test:

%.o: 						%.c
							$(CC) $(CFLAGS) -Iincludes -c -o $@ $<

clean:
							rm -f $(OBJECTS)

fclean:						clean
							rm -f $(NAME)

re:							fclean all
