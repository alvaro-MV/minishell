NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -v

RM = rm -f

SRC =  	data_structs/dictionary.c \
		data_structs/dictionary2.c \
		data_structs/dynamic_array.c \
		execution/exec_builtin_cmd.c \
		execution/exec_io_redir.c \
		execution/exec_utils.c \
		execution/executor.c \
		execution/heredoc.c \
		expansion/expand_str.c \
		parser/buffer_AST.c \
		parser/free_AST.c \
		parser/parse_command.c \
		parser/parse_io_redir.c \
		parser/parse_pipe.c \
		parser/parser.c \
		parser/print_AST.c \
		tokenizer/tokenizer_utils.c \
		tokenizer/tokenizer.c \
		environment.c \
		main.c \
		builtins/echo.c \

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
