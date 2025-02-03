NAME := philo
SOURCE := main.c data.c philo.c monitor.c misc.c
OBJECT := $(SOURCE:.c=.o)
CFLAGS := -Wall -Wextra -Werror
LDLIBS := -lpthread

$(NAME): $(OBJECT)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

all: $(NAME)

debug-thread:
	make re CFLAGS="$(CFLAGS) -g -fsanitize=thread"

debug:
	make re CFLAGS="$(CFLAGS) -g -fsanitize=address,leak"

clean:
	$(RM) $(OBJECT)

fclean: clean
	$(RM) $(NAME)

test: all
	setarch -R ./$(NAME) 4 410 200 200

re: fclean all
