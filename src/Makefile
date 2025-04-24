SHELL = /bin/bash

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

NAME = minishell

SRC =  scanner.c handle_error1.c handle_error2.c \
	   tokens.c env_expansion.c minishell.c utils.c \
	   signal.c\

LIB = ../lib

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIB)/libft.a
	@clear
	@$(CC) $(OBJ) -L$(LIB) -lft -lreadline -o $(NAME)
	@echo -n "  Compiling"
	@$(MAKE) -s loading
	@clear
	@echo -e "\033[32m ✓ \033[0m Compilation successful!"

$(LIB)/libft.a:
	@make -s -C $(LIB)

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -s -C $(LIB)
	@rm -f $(OBJ)

fclean: clean
	@make fclean -s -C $(LIB)
	@clear
	@echo -n "  Cleaning"
	@$(MAKE) -s loading
	@rm -f $(NAME)
	@echo -e "\033[32m ✓ \033[0m Clean complete!"

re: fclean all

loading:
	@spin=("⠁" "⠃" "⠇" "⠧" "⠷" "⠿" "⠷" "⠧" "⠇" "⠃"); \
	for i in {1..1}; do \
		for j in $${spin[@]}; do \
			echo -ne "$$j\r"; \
			sleep 0.1; \
		done; \
	done

.PHONY:	all clean fclean re
