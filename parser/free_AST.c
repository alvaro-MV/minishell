/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_AST.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:47:41 by alvmoral          #+#    #+#             */
/*   Updated: 2025/05/17 11:02:40 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_io_redir(t_io_redir *io_redir)
{
	t_io_redir	*tmp_io_redir;

	if (io_redir)
	{
		tmp_io_redir = io_redir->next;
		free(io_redir);
		free_io_redir(tmp_io_redir);
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp_cmd;
	char	**cmds_for_free;

	while (cmd)
	{
		free_io_redir(cmd->cmd_prefix);
		free_io_redir(cmd->cmd_suffix);
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
	if (!sequence)
		return ;
	free_cmd(sequence->cmd);
	if (sequence->next)
		free_ast(sequence->next);
	free(sequence);
}
