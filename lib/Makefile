CC = cc 

CFLAGS = -Wall -Wextra -Werror

NAME = libft.a

SRC = ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_strlcpy.c ft_strlen.c\
      ft_atoi.c ft_strlcat.c ft_strncmp.c ft_strcmp.c ft_strchr.c ft_strrchr.c ft_strnstr.c ft_tolower.c\
	  ft_toupper.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_memchr.c ft_memcmp.c \
	  ft_strdup.c ft_calloc.c ft_substr.c ft_strjoin.c ft_strjoin_triple.c ft_strtrim.c ft_itoa.c ft_striteri.c\
	  ft_strmapi.c ft_split.c ft_putendl_fd.c ft_printf/ft_printf_fd.c ft_printf/ft_putchar_fd.c\
	  ft_printf/ft_putnbr_hex_low_fd.c ft_printf/ft_putnbr_hex_up_fd.c ft_printf/ft_putnbr_u_fd.c\
	  ft_printf/ft_putnbr_fd.c ft_printf/ft_putptr_fd.c ft_printf/ft_putstr_fd.c\

OBJ = $(SRC:.c=.o)

BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c\
	  	ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c\
	  	ft_lstmap_bonus.c\

OBJ_BONUS = $(BONUS:.c=.o)

all: $(NAME)

.c.o: 
	@$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

$(NAME): $(OBJ) $(OBJ_BONUS)
	@ar rcs $@ $(OBJ)
	@ar rcs $(NAME) $(OBJ_BONUS)
	
clean: 
	@rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re bonus
