/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_io_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:48:22 by alvmoral          #+#    #+#             */
/*   Updated: 2025/05/17 09:54:29 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	alloc_io_redir(t_io_redir **ptr__io_redir)
{
	*ptr__io_redir = ft_calloc(1, sizeof(t_io_redir));
	if (!*ptr__io_redir)
		return (0);
	return (1);
}

t_io_redir	*parse_io_redir(t_token **token_stream, t_dictionary *env)
{
	t_io_redir	*ret_io_redir;
	t_io_redir	*current_io_redir;
	t_io_redir	*tmp_io_redir;

	if (!alloc_io_redir(&ret_io_redir))
		return (NULL);
	current_io_redir = ret_io_redir;
	while ((*token_stream)->type == IO_OPERATOR)
	{
		current_io_redir->op = (*token_stream);
		(*token_stream)++;
		current_io_redir->filename = parse_word(token_stream);
		if (current_io_redir->filename == NULL
			|| current_io_redir->filename->type != FILENAME)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
			if ((*token_stream)->type == END)
				ft_putstr_fd("`newline'\n", 2);
			else
				ft_printf("%s\n", (*token_stream)->text);
			storage_signal(2, 1);
			return (free_io_redir(ret_io_redir), NULL);
		}
		if (!ft_strcmp(current_io_redir->op->text, "<<"))
		{
			if (here_doc(current_io_redir->filename->text, current_io_redir, env))
				return (free_io_redir(ret_io_redir), NULL);
		}
		if (!alloc_io_redir(&tmp_io_redir))
			return (free_io_redir(ret_io_redir), NULL);
		current_io_redir->next = tmp_io_redir;
		current_io_redir = tmp_io_redir;
	}
	current_io_redir->next = NULL;
	return (ret_io_redir);
}
