#ifndef BUILTIN_H
# define BUILTIN_H

# include "../minishell.h"

typedef enum echo_states
{
	INIT = 1,
	PRINT_WORD,
	FLAG
}	echo_states;

void	echo(char	**arguments);

#endif