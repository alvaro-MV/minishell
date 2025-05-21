/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:48:25 by alvmoral          #+#    #+#             */
/*   Updated: 2025/05/21 21:28:47 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_empty_cmd(t_cmd *cmd)
{
	if (cmd->cmd_prefix->op->type != END
		&& cmd->cmd_prefix->filename->type != END)
		return (0);
	if (cmd->cmd->full_idx > 0)
		return (0);
	if (cmd->cmd_suffix->op->type != END
		&& cmd->cmd_suffix->filename->type != END)
		return (0);
	if (cmd->next)
		return (0);
	return (1);
}

int	alloc_pipe_cmd(t_cmd_pipe **ptr_cmd_pipe)
{
	*ptr_cmd_pipe = ft_calloc(1, sizeof(t_cmd_pipe));
	if (!(*ptr_cmd_pipe))
		return (0);
	return (1);
}

t_cmd_pipe	*parse_cmd_pipe(t_token **token_stream, t_dictionary *env)
{
	t_cmd_pipe	*ret_cmd_pipe;
	t_cmd_pipe	*current_cmd_pipe;
	t_cmd_pipe	*tmp_cmd_pipe;

	if (!*token_stream)
		return (NULL);
	if (!alloc_pipe_cmd(&ret_cmd_pipe))
		return (NULL);
	ret_cmd_pipe->cmd = parse_cmd(token_stream, env);
	if (!ret_cmd_pipe->cmd)
		return (NULL);
	current_cmd_pipe = ret_cmd_pipe;
	while ((*token_stream)->type == PIPE_OPERATOR)
	{
		(*token_stream)++;
		if (!alloc_pipe_cmd(&tmp_cmd_pipe))
			return (NULL);
		tmp_cmd_pipe->cmd = parse_cmd(token_stream, env);
		// if (tmp_cmd_pipe->cmd == NULL)
		// 	return (NULL);
		current_cmd_pipe->next = tmp_cmd_pipe;
		current_cmd_pipe = tmp_cmd_pipe;
		if (!tmp_cmd_pipe->cmd)
			return (NULL);
	}
	current_cmd_pipe->next = NULL;
	return (ret_cmd_pipe);
}
