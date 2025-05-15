/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:20:37 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/15 18:46:13 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	handler_signint_child(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	close(0);
}

int	execute_sequence(t_cmd_pipe *sequence, t_dictionary *env, char **main_env,
		int n_cmd)
{
	t_exec	exec_vars;
	int		status;

	status = 0;
	signal(SIGINT, handler_signint_child);
	while (sequence)
	{
		exec_vars = (t_exec){sequence->cmd, env, main_env, dup(STDIN_FILENO)};
		status = execute_child(&exec_vars);
		sequence = sequence->next;
	}
	while (n_cmd--)
		wait(&status);
	if (WIFSIGNALED(status))
		return (127);
	else
		return (WEXITSTATUS(status));
	return (status);
}

int	executor(t_cmd_pipe *sequence, t_dictionary *env, char **main_env)
{
	t_exec	exec_vars;
	int		status;
	int		n_cmd;

	status = 0;
	(void)main_env;
	n_cmd = create_pipe_and_fds(sequence);
	expand_pipe_seq(sequence, env);
	if (n_cmd == 1 && is_builtin(sequence->cmd->cmd->darray))
	{
		exec_vars = (t_exec){sequence->cmd, env, main_env, dup(STDIN_FILENO)};
		status = execute_io_redir(&exec_vars);
		if (status != 0)
			return (status);
		status = run_builtin(&exec_vars);
		close_cmd_fds(sequence->cmd);
	}
	else
		execute_sequence(sequence, env, main_env, n_cmd);
	return (status);
}
