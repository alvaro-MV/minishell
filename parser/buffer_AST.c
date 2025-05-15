/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_AST.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:47:37 by alvmoral          #+#    #+#             */
/*   Updated: 2025/05/15 17:47:38 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	buffer_io_redir(t_io_redir *io_redir, char **buff_io)
{
	char	*buff_tmp_io;

	if (io_redir)
	{
		if (io_redir->op && io_redir->op->type != END)
		{
			buff_tmp_io = *buff_io;
			*buff_io = ft_strjoin(*buff_io, "(");
			free(buff_tmp_io);
			buff_tmp_io = *buff_io;
			*buff_io = ft_strjoin(*buff_io, io_redir->op->text);
			free(buff_tmp_io);
			buff_tmp_io = *buff_io;
			*buff_io = ft_strjoin(*buff_io, " ");
			free(buff_tmp_io);
		}
		if (io_redir->filename && io_redir->filename->type != END)
		{
			buff_tmp_io = *buff_io;
			*buff_io = ft_strjoin(*buff_io, io_redir->filename->text);
			free(buff_tmp_io);
			buff_tmp_io = *buff_io;
			*buff_io = ft_strjoin(*buff_io, ") ");
			free(buff_tmp_io);
		}
		buffer_io_redir(io_redir->next, buff_io);
	}
}

char	*buffer_cmd(t_cmd *cmd)
{
	char	*buff_cmd;
	char	*buff_tmp_cmd;
	char	**command_list;
	command	*cmd_array;
	t_cmd	*tmp_cmd;
	size_t	i;

	buff_cmd = ft_strdup("");
	tmp_cmd = cmd;
	while (cmd)
	{
		buffer_io_redir(cmd->cmd_prefix, &buff_cmd);
		buffer_io_redir(cmd->cmd_suffix, &buff_cmd);
		cmd = cmd->next;
	}
	buff_tmp_cmd = buff_cmd;
	buff_cmd = ft_strjoin(buff_cmd, "{ ");
	free(buff_tmp_cmd);
	while (tmp_cmd)
	{
		i = 0;
		cmd_array = tmp_cmd->cmd;
		command_list = (char **)cmd_array->darray;
		while (command_list && command_list[i])
		{
			buff_tmp_cmd = buff_cmd;
			buff_cmd = ft_strjoin(buff_cmd, command_list[i]);
			free(buff_tmp_cmd);
			buff_tmp_cmd = buff_cmd;
			buff_cmd = ft_strjoin(buff_cmd, " ");
			free(buff_tmp_cmd);
			i++;
		}
		tmp_cmd = tmp_cmd->next;
	}
	buff_tmp_cmd = buff_cmd;
	buff_cmd = ft_strjoin(buff_cmd, "} ");
	free(buff_tmp_cmd);
	return (buff_cmd);
}

void	buffer_ast(t_cmd_pipe *sequence, char **AST)
{
	char	*tmp_ast;
	char	*buff_cmd;

	tmp_ast = *AST;
	buff_cmd = buffer_cmd(sequence->cmd);
	*AST = ft_strjoin(*AST, buff_cmd);
	free(tmp_ast);
	free(buff_cmd);
	if (sequence->next)
	{
		tmp_ast = *AST;
		*AST = ft_strjoin(*AST, "| \n");
		free(tmp_ast);
		buffer_ast(sequence->next, AST);
	}
}
