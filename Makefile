NAME = minishell

MY_SOURCES = minishell.c invalid_input.c
MY_OBJECTS = $(MY_SOURCES:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Ilibreria #-g3 -fsanitize=thread

$(NAME): $(MY_OBJECTS)
	@${MAKE} -C ./Libft
	@${MAKE} -C ./Pipex

	@$(CC) $(CFLAGS) $(MY_OBJECTS) -o $(NAME) ./Libft/libft.a ./Pipex/pipex.a -lreadline

all: ${NAME}

%.o: %.c
	$(CC) -c $< -o $@

clean:
	@${MAKE} -C ./Libft fclean
	@${MAKE} -C ./Pipex fclean
	rm -f $(MY_OBJECTS)

fclean: clean
		rm -f $(NAME)

re:		fclean all

.PHONY: all, clean, fclean, re
