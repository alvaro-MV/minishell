#ifndef BUILTINS_H
# define BUILTINS_H



struct s_exec;
typedef struct s_exec t_exec;

# include "../minishell.h"
# include <stddef.h>
# include <unistd.h>

typedef enum echo_states
{
	INIT = 1,
	PRINT_WORD,
	FLAG
}	echo_states;

void	echo(char	**arguments);
void	export(t_exec *exec);
int		pwd2(void);

#endif