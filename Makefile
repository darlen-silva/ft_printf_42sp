NAME	= libftprintf.a

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -pedantic

SRC		= ft_printf.c ft_printf_utils.c
HEADER	= ft_printf.h

OBJ		= $(SRC:.c=.o)

all: $(NAME) $(OBJ)

$(NAME): $(SRC) $(HEADER)
	$(CC) $(CFLAGS) -c $(SRC)
	ar -rcs $(NAME) $(OBJ)

test: $(NAME)
	@$(CC) -g main.c -L. -lftprintf
	@./a.out | cat -e

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
