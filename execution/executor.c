/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:20:37 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/18 16:03:31 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	handler_signint_child(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	storage_signal(sig + 128, 1);
	close(0);
}

int	execute_sequence(t_cmd_pipe *sequence, t_dictionary *env, int n_cmd)
{
	t_cmd_pipe *seq_start;
	t_exec	exec_vars;
	int		status;
	int		*pids;
	int		i;

	status = 0;
	pids = ft_calloc(n_cmd, sizeof(pid_t));
	signal(SIGINT, handler_signint_child);
	i = 0;
	seq_start = sequence;
	while (sequence)
	{
		exec_vars = (t_exec){sequence->cmd, env};
		pids[i++] = execute_child(&exec_vars, seq_start);
		close_cmd_fds(sequence->cmd);
		sequence = sequence->next;
	}
	i = 0;
	while (i < n_cmd)
		waitpid(pids[i++], &status, 0);
	free(pids);
	return (WEXITSTATUS(status));
}

int	execute_builtin(t_exec *exec_vars)
{
	int	status;

	status = execute_io_redir(exec_vars);
	if (status != 0)
		return (status);
	if (exec_vars->cmd->fds[0] != 0 && dup2(exec_vars->cmd->fds[0], 0) == -1)
		write(1, "Siiiiiii\n", 10);
	if (exec_vars->cmd->fds[1] != 1 && dup2(exec_vars->cmd->fds[1], 1) == -1)
		write(1, "Siiiiiii\n", 10);
	status = run_builtin(exec_vars);
	close_cmd_fds(exec_vars->cmd);
	return (status);
}

int	executor(t_cmd_pipe *sequence, t_dictionary *env)
{
	t_exec	exec_vars;
	int		status;
	int		n_cmd;

	status = 0;
	n_cmd = create_pipe_and_fds(sequence);
	expand_pipe_seq(sequence, env);
	if (n_cmd == 1 && is_builtin(sequence->cmd->cmd->darray))
	{
		exec_vars = (t_exec){sequence->cmd, env};
		return (execute_builtin(&exec_vars));
	}
	else
		status = execute_sequence(sequence, env, n_cmd);
	return (status);
}
