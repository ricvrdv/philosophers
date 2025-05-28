##############################################################################
# CONFIG                                                                     #
##############################################################################

NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

##############################################################################
# SOURCE FILES                                                               #
##############################################################################

SRC = main.c \
	parse.c \
	init.c \
	utils.c \
	safe.c

OBJ = $(SRC:.c=.o)

##############################################################################
# COLORS                                                                     #
##############################################################################

RED = \033[1;31m

GREEN = \033[1;32m

RESET = \033[0m

##############################################################################
# RULES                                                                      #
##############################################################################

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)Compilation Successful!$(RESET)"

clean:
	@if ls $(OBJ) 1> /dev/null 2>&1; then \
		$(RM) $(OBJ); \
		echo "$(RED)Intermediate object files removed:$(RESET)\n$(OBJ)"; \
	else \
		echo "$(RED)No object files to remove.$(RESET)"; \
	fi

fclean: clean
	@if [ -f $(NAME) ]; then \
		$(RM) $(NAME); \
		echo "$(RED)Compiled executable removed:$(RESET)\n$(NAME)"; \
	else \
		echo "$(RED)No executable to remove.$(RESET)"; \
	fi

re: fclean all

.PHONY: all clean fclean re

##############################################################################
