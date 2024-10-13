NAME = minishell
SRCS = main.c parsing/parsing.c parsing/ft_strtok.c parsing/check_complete.c \
parsing/ft_strjoin.c  execution/pwd.c execution/decider.c \
execution/echo.c execution/nbuilt.c execution/nbuilt2.c execution/tools/minilibft.c execution/tools/split.c execution/env.c execution/chdir.c execution/initargs.c \
parsing/srchenv.c parsing/remove_quotes.c parsing/helper.c parsing/expand.c execution/export.c  \
execution/hdoc.c execution/pipe.c parsing/split_pipe.c execution/exit.c execution/unset.c parsing/parsing_helper.c parsing/parsing_helper2.c \
execution/tools/gcollector.c


OBJS = $(SRCS:.c=.o)
FLAGS = -Wall -Wextra -Werror
HEADER = minishell.h
READLINEDIR  =  $(shell brew --prefix readline)

all: $(NAME)
%.o: %.c $(HEADER)
	$(CC) -c $< -o $@ -I $(READLINEDIR)/include
$(NAME): $(OBJS)
	$(CC)   $(OBJS) -o $(NAME) -L $(READLINEDIR)/lib -lreadline -lhistory -g -O0
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: clean