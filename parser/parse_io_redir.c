/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_io_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:48:22 by alvmoral          #+#    #+#             */
/*   Updated: 2025/05/23 01:25:24 by alvmoral         ###   ########.fr       */
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

int	bfile(t_io_redir *c, t_io_redir *r, t_token **tk, t_dictionary *e)
{
	if (!c->filename
		|| c->filename->type != FILENAME)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
		if ((*tk)->type == END)
			ft_putstr_fd("`newline'\n", 2);
		else
			ft_printf("%s\n", (*tk)->text);
		storage_signal(2, 1);
		return (free_io_redir(r), 0);
	}
	if (c->filename
		&& !ft_strcmp(c->op->text, "<<"))
	{
		if (here_doc(tk, c, e))
			return (free_io_redir(r), 0);
	}
	return (1);
}

void	get_redir_tokens(t_io_redir *current_io_redir, t_token **token_stream)
{
	current_io_redir->op = ft_calloc(1, sizeof(t_token));
	current_io_redir->op->text = ft_strdup((*token_stream)->text);
	(*token_stream)++;
	current_io_redir->filename = parse_word(token_stream);
}

void	advance_io_redir(t_io_redir **cur, t_io_redir *tmp, t_io_redir **ret)
{
	if (!*cur)
	{
		*cur = tmp;
		*ret = (*cur);
	}
	else
	{
		(*cur)->next = tmp;
		(*cur) = tmp;
	}
}

t_io_redir	*parse_io_redir(t_token **token_stream, t_dictionary *env)
{
	t_io_redir	*ret_io_redir;
	t_io_redir	*current_io_redir;
	t_io_redir	*tmp_io_redir;

	current_io_redir = NULL;
	ret_io_redir = NULL;
	while ((*token_stream)->type == IO_OPERATOR)
	{
		if (!alloc_io_redir(&tmp_io_redir))
			return (free_io_redir(ret_io_redir), NULL);
		advance_io_redir(&current_io_redir, tmp_io_redir, &ret_io_redir);
		get_redir_tokens(current_io_redir, token_stream);
		if (!bfile(current_io_redir, ret_io_redir, token_stream, env))
			return (NULL);
	}
	if (!ret_io_redir)
		alloc_io_redir(&ret_io_redir);
	else
		alloc_io_redir(&current_io_redir->next);
	return (ret_io_redir);
}
