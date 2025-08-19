NAME = philo

CC = cc

SRC = src/main.c \
      src/init.c \
      src/errors.c \
      src/utils.c \
      src/routine_philo.c

OBJ_DIR = obj

OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

INCLUDES = includes/philosophers.h

CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lpthread

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: src/%.c $(INCLUDES) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -Iincludes -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean all re