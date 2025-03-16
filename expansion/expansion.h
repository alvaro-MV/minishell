#ifndef EXPANSION_H
# define EXPANSION_H

# include "../minishell.h"

typedef enum expand_states
{
	WORD = 1,
	DOUBLE_QUOTE,
	SINGLE_QUOTE,
	ENV_VAR
}	expand_states;

char	*expand_str(char *str, t_dictionary *env);

#endif