NAME = philo

CC = cc

SRC = src/main.c \
      src/init.c \
      src/errors.c \
      src/routine_alone.c \
      src/philo.c \
      src/routine.c \
      src/end_conditions.c \
      src/time_functions.c \
      src/parcing.c

OBJ_DIR = obj

OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

INCLUDES = includes/philosophers.h

# ThreadSanitizer activé
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g -O1
LDFLAGS = -pthread -fsanitize=thread -g

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

# Règle pour compiler SANS ThreadSanitizer
normal:
	$(MAKE) fclean
	$(MAKE) CFLAGS="-Wall -Wextra -Werror -g" LDFLAGS="-pthread -g"

# Règle pour compiler avec ThreadSanitizer
tsan:
	$(MAKE) fclean
	$(MAKE) CFLAGS="-Wall -Wextra -Werror -fsanitize=thread -g -O1" LDFLAGS="-pthread -fsanitize=thread -g"

# Règle pour Helgrind
helgrind:
	$(MAKE) fclean
	$(MAKE) CFLAGS="-Wall -Wextra -Werror -g -O0" LDFLAGS="-pthread -g"

.PHONY: clean fclean all re normal tsan helgrind