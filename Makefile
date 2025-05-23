
NAME = minishell
SRCS = main.c parsing/parsing.c parsing/ft_strtok.c parsing/check_complete.c \
execution/pwd.c execution/decider.c \
execution/echo.c execution/nbuilt.c execution/nbuilt2.c execution/tools/minilibft.c execution/tools/split.c execution/env.c execution/chdir.c execution/initargs.c \
parsing/srchenv.c parsing/remove_quotes.c parsing/helper.c parsing/expand.c execution/export.c  \
	parsing/split_pipe.c execution/exit.c execution/unset.c parsing/parsing_helper.c parsing/parsing_helper2.c \
execution/tools/gcollector.c execution/tools/minilibft2.c execution/tools/minilibft3.c execution/tools/minilibft4.c \
execution/executemulti.c execution/executesingle.c parsing/parsing_helper3.c parsing/expand_2.c parsing/expand_3.c \
parsing/helper_2.c parsing/parsing_helper4.c execution/exit2.c execution/chdir2.c execution/echo2.c execution/export2.c execution/export3.c execution/env2.c\
execution/nbuilt3.c parsing/ft_random.c execution/waiter.c main2.c main3.c parsing/helper3.c ft_signals.c execution/tools/minilibft5.c parsing/remove_tab.c\
parsing/hdocounter.c

OBJS = $(SRCS:.c=.o)
FLAGS = -Wall -Wextra -Werror
HEADER = minishell.h
READLINEDIR  =  $(shell brew --prefix readline)

all: $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@ -I $(READLINEDIR)/include
$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) -L $(READLINEDIR)/lib -lreadline -lhistory 
	# rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
clean:
	rm -f $(OBJS)
re: fclean all
.PHONY: clean