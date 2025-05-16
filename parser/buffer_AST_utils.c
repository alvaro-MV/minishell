/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_AST_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:52:46 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/16 18:14:57 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	process_io_op(t_io_redir *io_redir, char **buff_io)
{
	char	*buff_tmp_io;

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
}

void	process_io_filename(t_io_redir *io_redir, char **buff_io)
{
	char	*buff_tmp_io;

	if (io_redir->filename && io_redir->filename->type != END)
	{
		buff_tmp_io = *buff_io;
		*buff_io = ft_strjoin(*buff_io, io_redir->filename->text);
		free(buff_tmp_io);
		buff_tmp_io = *buff_io;
		*buff_io = ft_strjoin(*buff_io, ") ");
		free(buff_tmp_io);
	}
}

void	buffer_io_redir(t_io_redir *io_redir, char **buff_io)
{
	if (io_redir)
	{
		process_io_op(io_redir, buff_io);
		process_io_filename(io_redir, buff_io);
		buffer_io_redir(io_redir->next, buff_io);
	}
}
