/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:38:07 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/19 18:59:25 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	create_pipe_and_fds(t_cmd_pipe *sequence)
{
	int	pipe_fd[2];
	int	old_fd;
	int	n_cmd;

	old_fd = 0;
	n_cmd = 1;
	while (sequence->next)
	{
		if (pipe(pipe_fd) == -1)
			write(1, "Error: Failed to create pipe\n", 29);
		sequence->cmd->fds[0] = old_fd;
		sequence->cmd->fds[1] = pipe_fd[1];
		old_fd = pipe_fd[0];
		n_cmd++;
		sequence = sequence->next;
	}
	sequence->cmd->fds[0] = old_fd;
	sequence->cmd->fds[1] = 1;
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
