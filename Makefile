NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

RM = rm -f

SRC =  	data_structs/dictionary.c \
		data_structs/dictionary_utils.c \
		data_structs/dictionary2.c \
		data_structs/dynamic_array.c \
		expansion/expand_str.c \
		expansion/expand_utils.c \
		execution/exec_builtin_cmd.c \
		execution/exec_io_redir.c \
		execution/exec_utils.c \
		execution/executor_utils.c \
		execution/executor.c \
		parser/buffer_AST.c \
		parser/free_AST.c \
		parser/parse_command.c \
		parser/parse_io_redir.c \
		parser/parse_pipe.c \
		parser/parser.c \
		parser/print_AST.c \
		parser/heredoc.c \
		tokenizer/tokenizer_utils.c \
		tokenizer/tokenizer.c \
		tokenizer/tokenizer_quotes.c \
		environment.c \
		main.c \
		builtins/echo.c \
		builtins/export.c \
		builtins/export_utils.c \
		builtins/env.c \
		builtins/cd.c \
		builtins/exit.c \
		builtins/pwd.c \
		builtins/unset.c \
		signals.c \

		

LIB = libft/libft.a

OBJS = $(SRC:.c=.o)

all = $(NAME)

$(NAME) : $(OBJS)
	@echo "${CIAN}Compiling...${NC}"
	@$(MAKE) -C libft
	@$(CC) $(CFLAGS) $(OBJS) $(LIB) -lreadline -o $(NAME)
	@echo "${LGREEN}Program compiled✅${NC}"

clean :
	@$(MAKE) clean -C libft
	@$(RM) $(OBJS)
	@echo "${MAGENTA}Objects deleted🧹${NC}"

fclean : clean
	@$(MAKE) fclean -C libft
	@$(RM) $(NAME)
	@echo "${MAGENTA}All clean✨${NC}"

re : fclean all

.PHONY: all clean fclean re
