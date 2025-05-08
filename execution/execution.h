#ifndef EXECUTION_H
# define EXECUTION_H

# include "../minishell.h"
# include "../builtins/builtins.h"

typedef struct s_exec
{
	t_cmd			*cmd;
	t_dictionary	*env;
	char			**main_env;
	int				saved_stdin;
}					t_exec;

int		executor(t_cmd_pipe *sequence, t_dictionary *env, char **main_env);
int		execute_io_redir(t_exec *exec);
int		is_builtin(char **cmd_args);
int		run_builtin(t_exec *exec);
int		execute_child(t_exec *exec_vars);
void	close_cmd_fds(t_cmd *cmd);
int		here_doc(char *delimiter, t_exec *exec);
int		traverse_io_redir(t_io_redir *ix, t_exec *exec);
char	**create_args(t_cmd *cmd);
void	signals_heredoc(char **input, int *exit);

#endif