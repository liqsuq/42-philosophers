NAME := philo
SOURCE := main.c thread.c misc.c
OBJECT := $(SOURCE:.c=.o)
CFLAGS := -Wall -Wextra -Werror
LDLIBS := -lpthread

$(NAME): $(OBJECT)

all: $(NAME)

clean:
	$(RM) $(OBJECT)

fclean: clean
	$(RM) $(NAME)

re: fclean all
