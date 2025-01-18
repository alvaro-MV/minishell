#ifndef TOKENIZER_H
# define TOKENIZER_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <editline/readline.h>
# include <readline/history.h>
# include "dynamic_array.h"
# include "libft/include/libft.h"

typedef enum	token_type
{
	OPERATOR=1,
	FILENAME,
	COMMAND,
	END
}	token_type;

typedef struct	s_token
{
	token_type	type;
	char		*text;
}		t_token;


t_darray	*tokenizer_str(char *argv);

#endif