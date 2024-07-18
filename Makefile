NAME = minishell
SRCS = main.c parsing.c ft_strtok.c check_complete.c \
ft_strjoin.c  execution/pwd.c execution/decider.c \
execution/echo.c execution/nbuilt.c tools/minilibft.c tools/split.c
OBJS = $(SRCS:.c=.o)
HEADER = minishell.h
all: $(NAME)
# %.o: %.c $(HEADER)
# 	cc -c  $< -o $@ -Wall -Wextra -Werror
$(NAME): $(OBJS)
	cc  $(SRCS) -o $(NAME) -lreadline
	make clean
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: clean