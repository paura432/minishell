NAME = minishell

MY_SOURCES = minishell.c

MY_OBJECTS = $(MY_SOURCES:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Ilibreria #-g3 -fsanitize=thread

all: ${NAME}
${NAME}: ${MY_OBJECTS}
	@${CC} ${CFLAGS} ${MY_OBJECTS} -o ${NAME} -lreadline

clean:
		rm -f $(MY_OBJECTS)

fclean: clean
		rm -f $(NAME)

re:		fclean all

.PHONY: all, clean, fclean, re
