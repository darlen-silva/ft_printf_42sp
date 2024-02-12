NAME	= libftprintf.a

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -pedantic
INC		= libft/

SRC		= ft_printf.c
HEADER	= ft_printf.h

OBJ		= $(SRC:.c=.o)

all:
	$(CC) $(CFLAGS) -c $(SRC)
	ar -rcs $(NAME) $(OBJ)

clean:
	# make fclean -C libft
	rm	-f $(OBJ)

fclean: clean
	make fclean -C libft
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
