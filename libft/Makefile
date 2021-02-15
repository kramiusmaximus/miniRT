NAME = libft.a
SOURCES_DIRECTORY = srcs
SOURCES = $(shell find $(SOURCES_DIRECTORY) -name '*.c')
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))
HEADERS_DIRECTORY = ./includes/
HEADERS_LIST = libft.h get_next_line.h libftprintf.h
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all:						${NAME}

$(NAME):					${OBJECTS} $(HEADERS)
							ar rc $(NAME) $(OBJECTS)
							ranlib $(NAME)

%.o:						%.c
							$(CC) $(CFLAGS) -I$(HEADERS_DIRECTORY) -c -o $@ $<

clean:
							rm -f $(OBJECTS)

fclean:						clean
							rm -f $(NAME)

re:							fclean all
