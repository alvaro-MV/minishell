/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_AST.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:47:41 by alvmoral          #+#    #+#             */
/*   Updated: 2025/05/19 19:44:34 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_io_redir(t_io_redir *io_redir, int parent)
{
	t_io_redir	*tmp_io_redir;

	while (io_redir)
	{
		tmp_io_redir = io_redir->next;
		if (io_redir->hd_name && parent == 1)
			unlink(io_redir->hd_name);
		free(io_redir->hd_name);
		if (io_redir->filename)
		{
			free(io_redir->filename->text);
			free(io_redir->filename);
		}
		if (io_redir->op)
		{
			free(io_redir->op->text);
			free(io_redir->op);
		}
		free(io_redir);
		io_redir = tmp_io_redir;
	}
}

void	free_cmd(t_cmd *cmd, int parent)
{
	t_cmd	*tmp_cmd;
	char	**cmds_for_free;

	while (cmd)
	{
		free_io_redir(cmd->cmd_prefix, parent);
		free_io_redir(cmd->cmd_suffix, parent);
		cmds_for_free = (char **)cmd->cmd->darray;
		while (*cmds_for_free)
		{
			free(*cmds_for_free);
			cmds_for_free++;
		}
		free_darray(cmd->cmd);
		tmp_cmd = cmd->next;
		free(cmd);
		cmd = tmp_cmd;
	}
}

void	free_ast(t_cmd_pipe *sequence)
{
	t_cmd_pipe *tmp;

	while (sequence)
	{
		tmp = sequence->next;
		free_cmd(sequence->cmd, 1);
		free(sequence);
		sequence = tmp;
	}
}

// /* Nuevo helper: libera la tubería completa */
// void	free_cmd_pipe(t_cmd_pipe *pipe)
// {
// 	t_cmd_pipe	*next;

// 	while (pipe)
// 	{
// 		next = pipe->next;
// 		free_cmd(pipe->cmd);
// 		free(pipe);
// 		pipe = next;
// 	}
// }
