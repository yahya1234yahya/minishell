NAME = minishell
SRCS = main.c parsing/parsing.c parsing/ft_strtok.c parsing/check_complete.c \
parsing/ft_strjoin.c  execution/pwd.c execution/decider.c \
execution/echo.c execution/nbuilt.c execution/nbuilt2.c execution/tools/minilibft.c execution/tools/split.c execution/env.c execution/chdir.c execution/initargs.c \
parsing/srchenv.c parsing/remove_quotes.c parsing/helper.c parsing/expand.c execution/export.c execution/tools/get_next_line.c \
execution/tools/get_next_line_utils.c execution/redirect.c
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