/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_AST.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:48:31 by alvmoral          #+#    #+#             */
/*   Updated: 2025/05/16 17:04:10 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_io_redir(t_io_redir *io_redir)
{
	if (io_redir)
	{
		if (io_redir->op && io_redir->op->type != END)
			ft_printf("(%s ", io_redir->op->text);
		if (io_redir->filename && io_redir->filename->type != END)
			ft_printf("%s) ", io_redir->filename->text);
		print_io_redir(io_redir->next);
	}
}

void	print_io_redirections(t_cmd *cmd)
{
	while (cmd)
	{
		print_io_redir(cmd->cmd_prefix);
		print_io_redir(cmd->cmd_suffix);
		cmd = cmd->next;
	}
}

void	print_cmd(t_cmd *cmd)
{
	char		**command_list;
	t_command	*cmd_array;
	t_cmd		*tmp_cmd;
	size_t		i;

	print_io_redirections(cmd);
	ft_printf("{ ");
	tmp_cmd = cmd;
	while (tmp_cmd)
	{
		i = 0;
		cmd_array = tmp_cmd->cmd;
		command_list = (char **)cmd_array->darray;
		while (command_list && command_list[i])
		{
			ft_printf("%s ", command_list[i]);
			i++;
		}
		tmp_cmd = tmp_cmd->next;
	}
	ft_printf("} ");
}

void	print_ast(t_cmd_pipe *sequence)
{
	print_cmd(sequence->cmd);
	if (sequence->next)
	{
		ft_printf("| \n");
		print_ast(sequence->next);
	}
}
