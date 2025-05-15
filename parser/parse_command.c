/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:48:17 by alvmoral          #+#    #+#             */
/*   Updated: 2025/05/15 17:48:18 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	alloc_cmd(t_cmd **ptr_cmd)
{
	*ptr_cmd = ft_calloc(1, sizeof(t_cmd));
	if (!(*ptr_cmd))
		return (0);
	(*ptr_cmd)->cmd = alloc_darray(2, sizeof(char *));
	if (!(*ptr_cmd)->cmd)
		return (free(*ptr_cmd), 0);
	return (1);
}

int	parse_ix(t_io_redir **ptr_io_redir, t_token **token_stream,
		t_dictionary *env)
{
	*ptr_io_redir = parse_io_redir(token_stream, env);
	if (!*ptr_io_redir)
		return (0);
	return (1);
}

int	fill_cmd(t_token **stream, command **ptr_cmd, t_dictionary *env)
{
	int	n_cmd;

	n_cmd = 0;
	while ((*stream)->type == COMMAND)
	{
		if (!add_command(ptr_cmd, (*stream)->text, env, n_cmd))
			return (0);
		(*stream)++;
		n_cmd++;
	}
	if (!add_command(ptr_cmd, NULL, env, n_cmd))
		// NULL para el terminación y el último para el execve
		return (0);
	return (1);
}

t_cmd	*parse_cmd(t_token **token_stream, t_dictionary *env)
{
	t_cmd	*ret_cmd;
	t_cmd	*tmp_cmd;
	t_cmd	*current_cmd;

	if ((*token_stream)->type == PIPE_OPERATOR)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (NULL);
	}
	if (!alloc_cmd(&ret_cmd))
		return (NULL);
	current_cmd = ret_cmd;
	while ((*token_stream)->type != END
		&& (*token_stream)->type != PIPE_OPERATOR)
	{
		if (!parse_ix(&current_cmd->cmd_prefix, token_stream, env))
			return (free_cmd(ret_cmd), NULL);
		if (!fill_cmd(token_stream, &current_cmd->cmd, env))
			return (free_cmd(ret_cmd), NULL);
		if (!parse_ix(&current_cmd->cmd_suffix, token_stream, env))
			return (free_cmd(ret_cmd), NULL);
		if (!alloc_cmd(&tmp_cmd))
			return (free_cmd(ret_cmd), NULL);
		current_cmd->next = tmp_cmd;
		current_cmd = tmp_cmd;
	}
	current_cmd->next = NULL;
	return (ret_cmd);
}
