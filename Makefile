NAME	= libftprintf.a

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -pedantic -mshstk -I.

SRC_DIR	= ./src
SRC		= ft_printf.c \
		  ft_printf_utils.c \
		  ft_printf_flags.c \
		  ft_printf_fmt.c

SRCS	= $(addprefix $(SRC_DIR)/, $(SRC))
HEADER	= ft_printf.h
OBJ		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	ar -rcs $(NAME) $(OBJ)

bonus: $(NAME)

test:
	@$(CC) $(SRC) -g main.c
	@./a.out

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
