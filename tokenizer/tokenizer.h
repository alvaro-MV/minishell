#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
//# include <editline/readline.h>
# include "../data_structs/dynamic_array.h"
# include "../libft/include/libft.h"
# include <readline/history.h>

typedef enum token_type
{
	IO_OPERATOR = 1,
	PIPE_OPERATOR,
	FILENAME,
	COMMAND,
	END
}				t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char		*text;
}				t_token;

int				add_token(t_darray **tokens, char *element);
int				is_simple_operator(char argv_char);
int				is_double_operator(char argv_char);
int				still_in_quote(char c, char quote);
t_darray		*tokenizer_str(char *argv);
t_token			*tokenizer_t_tokens(char **tokens_strings, size_t len);
void			free_tokens(t_token *tokens);

#endif