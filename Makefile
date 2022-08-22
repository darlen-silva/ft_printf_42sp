NAME	=	libftprintf.a

CFLAGS	=	-Wall -Wextra -Werror

SRC		=	ft_printf.c

HEADER	=	ft_printf.h

OBJ		=	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	ar -rcs --thin $(NAME) $(OBJ) libft/libft.a

.c.o: $(HEADER)
	cc $(CFLAGS) -c $< -o $@

clean:
	make fclean -C libft
	rm	-f $(OBJ)

fclean: clean
	make fclean -C libft
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
