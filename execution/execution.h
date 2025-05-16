/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:20:32 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/16 18:34:24 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../builtins/builtins.h"
# include "../minishell.h"
# include "../parser/parser.h"
# include <sys/stat.h>
# include <sys/types.h>

typedef struct s_exec
{
	t_cmd			*cmd;
	t_dictionary	*env;
	char			**main_env;
	int				saved_stdin;
}					t_exec;

char				*find_exec_in_path(char **path, char *exec);
int					call_execve(t_exec *exec);
int					run_builtin(t_exec *exec);
int					handle_child_process(t_exec *exec_vars);
int					override_fd(t_exec *exec, t_io_redir *redir, int flags,
						int idx);
int					traverse_io_redir(t_io_redir *ix, t_exec *exec);
int					execute_io_redir(t_exec *exec);
char				**create_args(t_cmd *cmd);
int					is_builtin(char **cmd_args);
void				close_cmd_fds(t_cmd *cmd);
int					create_pipe_and_fds(t_cmd_pipe *sequence);
void				expand_ix(t_io_redir *ix, t_dictionary *env);
void				expand_pipe_seq(t_cmd_pipe *sequence, t_dictionary *env);
void				handler_signint_child(int sig);
int					execute_sequence(t_cmd_pipe *sequence, t_dictionary *env,
						char **main_env, int n_cmd);
int					execute_builtin(t_exec *exec_vars, int *save_std);
int					executor(t_cmd_pipe *sequence, t_dictionary *env,
						char **main_env);
int					execute_child(t_exec *exec_vars);

#endif