#ifndef TOKENIZER_H
# define TOKENIZER_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../data_structs/dynamic_array.h"
# include "../libft/include/libft.h"

typedef enum	token_type
{
	IO_OPERATOR=1,
	PIPE_OPERATOR,
	FILENAME,
	COMMAND,
	END
}	token_type;

typedef struct	s_token
{
	token_type	type;
	char		*text;
}		t_token;


int			add_token(t_darray **tokens, char *element);
int			is_simple_operator(char argv_char);
int			is_double_operator(char argv_char);
int			still_in_quote(char c, char quote);
t_token		*tokenizer(char *line);
void		free_tokens(t_token *tokens);
void		traverse_quote(char *line, int *i);

#endif