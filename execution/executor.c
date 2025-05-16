/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:20:37 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/16 13:05:04 by alvmoral         ###   ########.fr       */
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
	int*	pids;

	status = 0;
	pids = ft_calloc(n_cmd, sizeof(pid_t));
	signal(SIGINT, handler_signint_child);
	int i = -1;
	while (sequence)
	{
		exec_vars = (t_exec){sequence->cmd, env, main_env,
			dup(STDIN_FILENO)};
		pids[++i] = execute_child(&exec_vars);
		sequence = sequence->next;
	}
	while (pids[i--])
		waitpid(pids[i], &status, 0);
	return (WEXITSTATUS(status));
}

int	executor(t_cmd_pipe *sequence, t_dictionary *env, char **main_env)
{
	t_exec	exec_vars;
	int		status;
	int		n_cmd;
	int		save_std[2];

	status = 0;
	save_std[0] = dup(STDIN_FILENO);
	save_std[1] = dup(STDOUT_FILENO);
	(void)main_env;
	n_cmd = create_pipe_and_fds(sequence);
	expand_pipe_seq(sequence, env);
	if (n_cmd == 1 && is_builtin(sequence->cmd->cmd->darray))
	{
		exec_vars = (t_exec){sequence->cmd, env, main_env, dup(STDIN_FILENO)};
		status = execute_io_redir(&exec_vars);
		if (status != 0)
			return (status);
		if (exec_vars.cmd->fds[0] != 0 && dup2(exec_vars.cmd->fds[0], 0)
			== -1)
			;
		if (exec_vars.cmd->fds[1] != 1 && dup2(exec_vars.cmd->fds[1], 1)
			== -1)
			;
		status = run_builtin(&exec_vars);
		close_cmd_fds(sequence->cmd);
		dup2(save_std[0], STDIN_FILENO);
		dup2(save_std[1], STDOUT_FILENO);
	}
	else
		status = execute_sequence(sequence, env, main_env, n_cmd);
	return (status);
}
