NAME = minishell
SRCS = main.c parsing/parsing.c parsing/ft_strtok.c parsing/check_complete.c \
execution/pwd.c execution/decider.c \
execution/echo.c execution/nbuilt.c execution/nbuilt2.c execution/tools/minilibft.c execution/tools/split.c execution/env.c execution/chdir.c execution/initargs.c \
parsing/srchenv.c parsing/remove_quotes.c parsing/helper.c parsing/expand.c execution/export.c  \
	parsing/split_pipe.c execution/exit.c execution/unset.c parsing/parsing_helper.c parsing/parsing_helper2.c \
execution/tools/gcollector.c execution/tools/minilibft2.c execution/tools/minilibft3.c execution/tools/minilibft4.c \
execution/executemulti.c execution/executesingle.c parsing/parsing_helper3.c parsing/expand_2.c parsing/expand_3.c \
parsing/helper_2.c parsing/parsing_helper4.c execution/exit2.c execution/chdir2.c execution/echo2.c execution/export2.c execution/export3.c execution/env2.c\
execution/nbuilt3.c


OBJS = $(SRCS:.c=.o)
FLAGS = -Wall -Wextra -Werror
HEADER = minishell.h
READLINEDIR  =  $(shell brew --prefix readline)

all: $(NAME)
%.o: %.c $(HEADER)
	$(CC) -c $< -o $@ -I $(READLINEDIR)/include -g -fsanitize=address
$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) -L $(READLINEDIR)/lib -lreadline -lhistory -g -fsanitize=address
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: clean


# lldb
# lldb ./minishell
# b function name or line number
# r
# n for next
# s for step to see inside the function
# p variable name to print the value
# q to quit
# x/s print the string