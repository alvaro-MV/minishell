/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:50:39 by alvmoral          #+#    #+#             */
/*   Updated: 2025/05/15 17:50:40 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	handler_signint_child(int sig)
{
	(void) sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	close(0);
}

int	create_pipe_and_fds(t_cmd_pipe *sequence)
{
	int	pipe_fd[2];
	int	old_fd[2];
	int	n_cmd;

	old_fd[0] = 0;
	old_fd[1] = 1;
	n_cmd = 1;
	while (sequence->next)
	{
		if (pipe(pipe_fd) == -1)
			write(1, "Nooooooooo\n", 12);
		sequence->cmd->fds[0] = old_fd[0];
		sequence->cmd->fds[1] = pipe_fd[1];
		old_fd[0] = pipe_fd[0];
		n_cmd++;
		sequence = sequence->next;
	}
	sequence->cmd->fds[0] = old_fd[0];
	sequence->cmd->fds[1] = old_fd[1];
	return (n_cmd);
}

void	expand_ix(t_io_redir *ix, t_dictionary *env)
{
	char	*tmp;

	while (ix && ix->next)
	{
		tmp = ix->filename->text;
		ix->filename->text = expand_str(tmp, env);
		free(tmp);
		ix = ix->next;
	}
}

void	expand_pipe_seq(t_cmd_pipe *sequence, t_dictionary *env)
{
	char	*tmp;
	t_cmd	*cmd;
	char	**cmd_array;
	int		i;

	while (sequence)
	{
		cmd = sequence->cmd;
		while (cmd)
		{
			i = -1;
			cmd_array = (char **)cmd->cmd->darray;
			while (cmd_array[++i])
			{
				tmp = cmd_array[i];
				cmd_array[i] = expand_str(tmp, env);
				free(tmp);
			}
			expand_ix(cmd->cmd_prefix, env);
			expand_ix(cmd->cmd_suffix, env);
			cmd = cmd->next;
		}
		sequence = sequence->next;
	}
}

int	executor(t_cmd_pipe *sequence, t_dictionary *env, char **main_env)
{
	t_exec	exec_vars;
	int		status;
	int		n_cmd;

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
	{
		signal(SIGINT, handler_signint_child);
		while (sequence)
		{
			exec_vars = (t_exec){sequence->cmd, env, main_env,
				dup(STDIN_FILENO)};
			status = execute_child(&exec_vars);
			sequence = sequence->next;
		}
		while (n_cmd--)
			wait(&status);
		if (WIFSIGNALED(status))
			return (127);
		else
			return (WEXITSTATUS(status));
	}
	return (status);
}
