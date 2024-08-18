NAME = minishell
SRCS = main.c parsing/parsing.c parsing/ft_strtok.c parsing/check_complete.c \
parsing/ft_strjoin.c  execution/pwd.c execution/decider.c \
execution/echo.c execution/nbuilt.c execution/nbuilt2.c execution/tools/minilibft.c execution/tools/split.c execution/env.c execution/chdir.c execution/initargs.c \
parsing/srchenv.c parsing/remove_quotes.c parsing/helper.c parsing/expand.c execution/export.c execution/tools/get_next_line.c \
execution/tools/get_next_line_utils.c execution/redirect.c execution/hdoc.c
OBJS = $(SRCS:.c=.o)
HEADER = minishell.h
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m
SMILEY = 😀
LINK = 🔗
CLEAN = 🧹
all: $(NAME)
$(NAME): $(OBJS)
	@echo "$(GREEN)$(SMILEY) Compiling...$(RESET)"
	@cc $(SRCS) -o $(NAME) -fsanitize=address -g -lreadline
	@make clean
	@echo "$(GREEN)$(SMILEY) Compilation completed!$(RESET)"
	@echo "   ▄▄▄▄███▄▄▄▄    ▄█  ███▄▄▄▄    ▄█     ▄████████    ▄█    █▄       ▄████████  ▄█        ▄█       "
	@echo " ▄██▀▀▀███▀▀▀██▄ ███  ███▀▀▀██▄ ███    ███    ███   ███    ███     ███    ███ ███       ███       "
	@echo " ███   ███   ███ ███▌ ███   ███ ███▌   ███    █▀    ███    ███     ███    █▀  ███       ███       "
	@echo " ███   ███   ███ ███▌ ███   ███ ███▌   ███         ▄███▄▄▄▄███▄▄  ▄███▄▄▄     ███       ███       "
	@echo " ███   ███   ███ ███▌ ███   ███ ███▌ ▀███████████ ▀▀███▀▀▀▀███▀  ▀▀███▀▀▀     ███       ███       "
	@echo " ███   ███   ███ ███  ███   ███ ███           ███   ███    ███     ███    █▄  ███       ███       "
	@echo " ███   ███   ███ ███  ███   ███ ███     ▄█    ███   ███    ███     ███    ███ ███▌    ▄ ███▌    ▄ "
	@echo "  ▀█   ███   █▀  █▀    ▀█   █▀  █▀    ▄████████▀    ███    █▀      ██████████ █████▄▄██ █████▄▄██ "                                                                                                                                                                                  
	@echo ""
	@echo "                                                                            ~ mboughra && ymouigui"                                                                                                                                                                                  

clean:
	@echo "$(YELLOW)$(CLEAN) Cleaning...$(RESET)"
	@rm -f $(OBJS)
	@echo "$(YELLOW)$(CLEAN) Clean completed!$(RESET)"

fclean: clean
	@echo "$(RED)$(CLEAN) Removing executable...$(RESET)"
	@rm -f $(NAME)
	@echo "$(RED)$(CLEAN) Removal completed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re