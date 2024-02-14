NAME	= libftprintf.a

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -pedantic

SRC		= ft_printf.c ft_printf_utils.c ft_printf_flags.c
HEADER	= ft_printf.h

OBJ		= $(SRC:.c=.o)

all: $(NAME) $(OBJ)

$(NAME): $(SRC) $(HEADER)
	$(CC) $(CFLAGS) -c $(SRC)
	ar -rcs $(NAME) $(OBJ)

bonus: $(NAME)

test:
	@$(CC) $(SRC) -g main.c
	@./a.out

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
