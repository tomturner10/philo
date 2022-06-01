
NAME = philo

SRCS = philo.c \
		errors.c \
		utils.c \
		init.c \
		lifecycle.c

FLAGS = -Werror -Wextra -Wall

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(SRCS) -o $(NAME)

clean:
	rm -f $(NAME)

fclean:
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean reg