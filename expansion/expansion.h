#ifndef EXPANSION_H
# define EXPANSION_H

# include "../data_structs/dictionary.h"
# include "../libft/include/libft.h"


typedef enum expand_states
{
	WORD = 1,
	DOUBLE_QUOTE,
	SINGLE_QUOTE,
	ENV_VAR
}	expand_states;

void	insert_special_params(t_dictionary **env);
char	*expand_str(char *str, t_dictionary *env);

#endif