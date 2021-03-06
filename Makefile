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

$(NAME):					${OBJECTS} ${OBJECTS_BONUS}
							make -C libft
							make -C mlx
							$(CC) -Llibft -lft -Lmlx -lmlx -framework OpenGL -framework AppKit $(OBJECTS) $(OBJECTS_BONUS) -o $(NAME)

test:						all
							./miniRT scenes/sq.rt

%.o: 						%.c ${HEADERS} ${HEADERS_BONUS}
							$(CC) $(CFLAGS) $(addprefix -I, $(INCLUDES_DIRECTORY)) -c -o $@ $<

clean:
							rm -f $(OBJECTS) $(OBJECTS_BONUS)
							make -C libft clean
							make -C mlx clean

fclean:						clean
							rm -f $(NAME)
							make -C libft fclean
							make -C mlx clean

re:							fclean all

bonus:						${OBJECTS} ${OBJECTS_BONUS}
							make -C libft
							make -C mlx
							$(CC) -Llibft -lft -Lmlx -lmlx -framework OpenGL -framework AppKit $(OBJECTS) $(OBJECTS_BONUS) -o $(NAME)

test_bonus:					bonus
							./miniRT scenes/transperancy.rt