/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_AST.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:47:37 by alvmoral          #+#    #+#             */
/*   Updated: 2025/05/16 16:53:02 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*build_command(t_cmd *cmd, char *buff_cmd)
{
	char		*buff_tmp_cmd;
	char		**command_list;
	t_command	*cmd_array;
	t_cmd		*tmp_cmd;
	size_t		i;

	tmp_cmd = cmd;
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
	return (buff_cmd);
}

char	*buffer_cmd(t_cmd *cmd)
{
	char	*buff_cmd;
	char	*buff_tmp_cmd;
	t_cmd	*tmp_cmd;

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
	buff_cmd = build_command(cmd, buff_cmd);
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
