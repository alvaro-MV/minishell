/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:20:32 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/15 18:51:41 by lvez-dia         ###   ########.fr       */
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

int					create_pipe_and_fds(t_cmd_pipe *sequence);
void				expand_pipe_seq(t_cmd_pipe *sequence, t_dictionary *env);
int					execute_sequence(t_cmd_pipe *sequence, t_dictionary *env,
						char **main_env, int n_cmd);
int					executor(t_cmd_pipe *sequence, t_dictionary *env,
						char **main_env);
int					execute_io_redir(t_exec *exec);
int					is_builtin(char **cmd_args);
int					run_builtin(t_exec *exec);
int					execute_child(t_exec *exec_vars);
void				close_cmd_fds(t_cmd *cmd);
int					traverse_io_redir(t_io_redir *ix, t_exec *exec);
char				**create_args(t_cmd *cmd);

#endif