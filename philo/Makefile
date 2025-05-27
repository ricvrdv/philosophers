NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

SRC = main.c \
	init.c \
	utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "\033[1;32mCompilation Successful!\033[0m"

clean:
	@if ls $(OBJ) 1> /dev/null 2>&1; then \
		$(RM) $(OBJ); \
		echo "\033[1;31mIntermediate object files removed:\033[0m\n$(OBJ)"; \
	else \
		echo "\033[1;31mNo object files to remove.\033[0m"; \
	fi

fclean: clean
	@if [ -f $(NAME) ]; then \
		$(RM) $(NAME); \
		echo "\033[1;31mCompiled executable removed:\033[0m\n$(NAME)"; \
	else \
		echo "\033[1;31mNo executable to remove.\033[0m"; \
	fi

re: fclean all

.PHONY: all clean fclean re
