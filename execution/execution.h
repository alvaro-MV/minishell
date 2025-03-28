#ifndef EXECUTION_H
# define EXECUTION_H

# include "../minishell.h"

typedef struct t_exec t_exec;

typedef struct t_exec
{
	t_cmd			*cmd;
	t_dictionary	*env;
	char			**main_env;
}					t_exec;

int		executor(t_cmd_pipe *sequence, t_dictionary *env);
int		execute_io_redir(t_exec exec);
int		is_builtin(char **cmd_args);
int		run_builtin(t_exec exec);
int		execute_child(t_exec exec_vars);
void	close_cmd_fds(t_cmd *cmd);

#endif