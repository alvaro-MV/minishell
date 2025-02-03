#include "parser.h"

int	alloc_cmd(t_cmd **ptr_cmd)
{
	*ptr_cmd = ft_calloc(1, sizeof(t_cmd));
	if (!(*ptr_cmd))
		return (0);
	(*ptr_cmd)->cmd = alloc_darray(2, sizeof(char *));
	if (!(*ptr_cmd)->cmd)
		return (free(*ptr_cmd), 0);
	return (1);
}

int	parse_ix(t_io_redir **ptr_io_redir, t_token **token_stream)
{
	*ptr_io_redir = parse_io_redir(token_stream);
	if (!*ptr_io_redir)
		return (0);
	return (1);
}

int	fill_cmd(t_token **token_stream, command **ptr_cmd)
{
	while ((*token_stream)->type == COMMAND)
	{
		if (!add_command(ptr_cmd, (*token_stream)->text))
			return (0);
		(*token_stream)++;
	}
	if (!add_command(ptr_cmd, NULL)) //NULL para el terminación y el último para el execve
		return (0);
	return (1);
}

t_cmd	*parse_cmd(t_token **token_stream)
{
	t_cmd	*ret_cmd;
	t_cmd	*tmp_cmd;
	t_cmd	*current_cmd;

	if ((*token_stream)->type == IO_OPERATOR) // Para el caso | |
	{
		ft_printf("minishell: syntax error near unexpected token `|'");
		return (NULL);
	}
	if (!alloc_cmd(&ret_cmd))
		return (NULL);
	current_cmd = ret_cmd;	
	while ((*token_stream)->type != END && (*token_stream)->type != PIPE_OPERATOR)
	{
		if (!parse_ix(&current_cmd->cmd_prefix, token_stream))
			return (NULL);

		// Meter tokens en el campo cmd hasta que el siguiente token != COMMAND

		if (!fill_cmd(token_stream, &current_cmd->cmd))
			return (NULL);

		// Parseo de redirecciones.
		if (!parse_ix(&current_cmd->cmd_suffix, token_stream))
			return (NULL);
		
		// Se reserva el siguiente comando.
		if (!alloc_cmd(&tmp_cmd))
			return (NULL);
		current_cmd = tmp_cmd;
	}
	current_cmd->next = NULL;
	return (ret_cmd);
}
