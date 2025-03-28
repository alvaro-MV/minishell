#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <editline/readline.h>
# include <readline/history.h> // Include this header for add_history
# include "tokenizer/tokenizer.h"
# include "data_structs/dynamic_array.h"
# include "data_structs/dictionary.h"
# include "libft/include/libft.h"
# include "parser/parser.h"
# include "expansion/expansion.h"
# include "execution/execution.h"
# include "data_structs/dictionary.h"
# include "builtins/builtins.h"

int		executor(t_cmd_pipe *sequence, t_dictionary *env);
char	*expand_str(char *str, t_dictionary *env);

#endif