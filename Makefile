NAME = minishell
COMP = gcc
CFLAGS = -Wall -Wextra -Werror -I.

BUILTINS = \
	builtins/builtin.c builtins/cd.c \
	builtins/echo.c builtins/env.c \
	builtins/exit.c builtins/export.c \
	builtins/pwd.c builtins/unset.c

EXECUTION = \
	execution/exec_child.c execution/exec.c \
	execution/find_cmd.c execution/heredoc.c \
	execution/redirection.c execution/signals.c \
	execution/heredoc_helper.c execution/heredoc_handlers.c

PARSING = \
	parsing/frees.c parsing/line_parse_helper.c \
	parsing/line_parse.c parsing/line_split_handler.c \
	parsing/line_split_helper.c parsing/line_split.c \
	parsing/var_expansion.c parsing/expand_helper.c \
	parsing/expanding.c parsing/parse_helper.c

UTILS = \
	utils/ft_split.c utils/libft_helper.c \
	utils/libft_helper2.c utils/utils_array.c \
	utils/utils_libft.c utils/utils_lst.c \
	utils/frees.c utils/cmd_utils.c

SRCS = $(BUILTINS) $(EXECUTION) $(PARSING) $(UTILS) initialization.c validation.c main.c
OBJS = $(SRCS:.c=.o)

VALGRIND_CMD = valgrind -s --log-file=valgrind_output.txt --suppressions=a.supp \
				--track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./minishell

all: $(NAME)

$(NAME): $(OBJS)
	$(COMP) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)

%.o: %.c
	$(COMP) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

good: all clean
	clear

valgrind: good
	$(VALGRIND_CMD)

norm:
	norminette > norm.out

.PHONY: all clean fclean re good
