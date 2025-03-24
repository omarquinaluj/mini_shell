
NAME := minishell
CFLAGS := -Wextra -Wall -Werror -fsanitize=address -g
LIBDEF_PATH := ./Libft
LIBDEF := $(LIBDEF_PATH)/libft.a
SRCS := check_exec.c free_exec.c parsing.c utils_file.c\
	env_utils.c ft_free.c main.c token.c utils_token.c\
	executing.c get_cmd.c tools_quotes.c extra_token.c\
	utils_exec.c casos_dolar.c envs_urgencia.c error.c\
	utils_parsing.c señales_full.c utils_señales.c\
	utils_readentry.c error2.c open_file.c check_exec2.c\
	builds_part1.c build_cd.c build_path.c build_echo.c\
	build_env.c build_exit.c build_export.c build_unset.c\
	build_pwd.c heredoc.c extension_main.c extension2_main.c\
	extension3_main.c  ft_t_exec.c utils_tool.c utils_tool2.c\
	utils_tool3.c

OBJS := ${SRCS:.c=.o}
LDFLAGS := -lreadline

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBDEF_PATH) all -s
	cc $(CFLAGS) $(OBJS) $(LIBDEF) -o $(NAME) $(LDFLAGS)

$(LIBDEF):
	$(MAKE) -C $(LIBDEF_PATH) all -s

clean:
	$(MAKE) -C $(LIBDEF_PATH) clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBDEF_PATH) fclean

re: fclean all

.PHONY: all clean fclean re

