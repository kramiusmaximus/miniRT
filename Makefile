NAME = miniRT
SOURCES_DIRECTORY = srcs
SOURCES = $(shell find $(SOURCES_DIRECTORY) \( -name '*.c' \! -name '*_bonus.c' \))
SOURCES_BONUS = $(shell find $(SOURCES_DIRECTORY) -name '*_bonus.c')
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))
OBJECTS_BONUS = $(patsubst %.c, %.o, $(SOURCES_BONUS))
INCLUDES_DIRECTORY = includes libft/includes mlx
HEADERS = $(shell find $(INCLUDES_DIRECTORY) \( -name '*.h' \! -name '*_bonus.h' \))
HEADERS_BONUS = $(shell find $(INCLUDES_DIRECTORY) -name '*_bonus.h')
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all:						${NAME}

$(NAME):					${OBJECTS}
							make -C libft
							make -C mlx
							$(CC) -Llibft -lft -Lmlx -lmlx -framework OpenGL -framework AppKit $(OBJECTS) -o $(NAME) libmlx.dylib

test:						all
							./miniRT scenes/vistovka1.rt

%.o: 						%.c ${HEADERS} ${HEADERS_BONUS}
							$(CC) $(CFLAGS) $(addprefix -I, $(INCLUDES_DIRECTORY)) -c -o $@ $<

clean:
							rm -f $(OBJECTS) $(OBJECTS_BONUS)
							make -C libft clean
							make -C mlx clean

fclean:						clean
							rm -f $(NAME)

re:							fclean all

bonus:						${OBJECTS} ${OBJECTS_BONUS}
							make -C libft
							make -C mlx
							$(CC) -Llibft -lft -Lmlx -lmlx -framework OpenGL -framework AppKit $(OBJECTS) $(OBJECTS_BONUS) -o $(NAME) libmlx.dylib

test_bonus:					bonus
							./miniRT scenes/vistovka1.rt

