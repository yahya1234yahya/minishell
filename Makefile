NAME = minishell
SRCS = main.c
OBJS = $(SRCS:.c=.o)
HEADER = minishell.h
all: $(NAME)
# %.o: %.c $(HEADER)
	# cc -c  $< -o $@ -Wall -Wextra -Werror
$(NAME): $(OBJS)
	cc -lreadline -Wall -Wextra -Werror $(SRCS) -o $(NAME)
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: clean