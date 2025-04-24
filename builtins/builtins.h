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
int		pwd2(void);
int		ft_env(char **args, t_exec *exec);
int		is_valid_name(char *name);
void	export_error(char *name);
int		export(t_exec *exec, char **arguments);

#endif