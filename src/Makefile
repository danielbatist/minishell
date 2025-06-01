SHELL = /bin/bash

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

NAME = minishell

SRC =  main/minishell.c \
       exec/execution.c \
	   parser/extract_cmd.c parser/parser.c parser/scanner.c parser/tokens.c\
	   expansion/env_expansion.c expansion/catch_env.c expansion/env_utils.c\
	   utils/handle_error1.c utils/handle_error2.c utils/free_things.c utils/utils.c\
	   utils/prints.c utils/signal.c\
	   redirect/redirects_utils.c redirect/redirects.c redirect/heredoc.c redirect/heredoc_utils.c\
	   redirect/open_file.c redirect/open_heredoc.c \
	   pipe/pipe.c builtins/builtins.c builtins/ft_echo.c builtins/ft_cd.c builtins/ft_env.c \
	   builtins/ft_exit.c builtins/ft_export.c builtins/ft_pwd.c builtins/ft_unset.c
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
