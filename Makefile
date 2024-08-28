NAME = minishell
SRCS = main.c parsing/parsing.c parsing/ft_strtok.c parsing/check_complete.c \
parsing/ft_strjoin.c  execution/pwd.c execution/decider.c \
execution/echo.c execution/nbuilt.c execution/nbuilt2.c execution/tools/minilibft.c execution/tools/split.c execution/env.c execution/chdir.c execution/initargs.c \
parsing/srchenv.c parsing/remove_quotes.c parsing/helper.c parsing/expand.c execution/export.c  \
execution/hdoc.c execution/pipe.c parsing/split_pipe.c
OBJS = $(SRCS:.c=.o)
HEADER = minishell.h

all: $(NAME) clean

$(NAME): $(OBJS)
	@echo "Compiling..."
	@cc $(SRCS) -o $(NAME) -lreadline
	@echo "Compilation completed!"

clean:
	@echo "Cleaning..."
	@rm -f $(OBJS)
	@echo "Clean completed!"

fclean: clean
	@echo "Removing executable..."
	@rm -f $(NAME)
	@echo "Removal completed!"

re: fclean all

.PHONY: all clean fclean re
