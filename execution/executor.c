/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:20:37 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/21 16:40:13 by alvaro           ###   ########.fr       */
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

int	execute_sequence(t_cmd_pipe *sequence, t_dictionary *env, int n_cmd, t_minishell *mini)
{
	t_cmd_pipe *seq_start;
	t_exec	exec_vars;
	int		status;
	int		i;

	status = 0;
	mini->pids = ft_calloc(n_cmd, sizeof(pid_t));
	signal(SIGINT, handler_signint_child);
	i = 0;
	seq_start = sequence;
	while (sequence)
	{
		exec_vars = (t_exec){sequence->cmd, env, mini};
		mini->pids[i++] = execute_child(&exec_vars, seq_start);
		close_cmd_fds(sequence->cmd);
		sequence = sequence->next;
	}
	i = 0;
	while (i < n_cmd)
		waitpid(mini->pids[i++], &status, 0);
	free(mini->pids);
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

int	executor(t_minishell *mini, t_cmd_pipe *sequence, t_dictionary *env)
{
	t_exec	exec_vars;
	int		status;
	int		n_cmd;

	status = 0;
	n_cmd = create_pipe_and_fds(sequence);
	expand_pipe_seq(sequence, env);
	mini->pids = NULL;
	if (n_cmd == 1 && is_builtin(sequence->cmd->cmd->darray))
	{
		exec_vars = (t_exec){sequence->cmd, env, mini};
		return (execute_builtin(&exec_vars));
	}
	else
		status = execute_sequence(sequence, env, n_cmd, mini);
	return (status);
}
