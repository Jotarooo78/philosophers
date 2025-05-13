NAME = philo

CC = cc

SRC = 

INCLUDES = includes/so_long.h

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g -lpthread

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C

$(NAME): $(OBJ)
	$(CC) $(OBJ)-o $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)
	$(MAKE) -C clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C fclean

re: fclean all

.PHONY: clean fclean all re
