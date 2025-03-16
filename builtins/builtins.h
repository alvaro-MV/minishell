#ifndef BUILTIN_H
# define BUILTIN_H

# include "../execution/execution.h"

typedef enum echo_states
{
	INIT = 1,
	PRINT_WORD,
	FLAG
}	echo_states;

void	echo(char	**arguments);
void	export(t_exec *exec);

#endif