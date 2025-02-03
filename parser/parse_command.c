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

t_cmd	*parse_cmd(t_token **token_stream)
{
	t_cmd	*ret_cmd;
	t_cmd	*tmp_cmd;
	t_cmd	*current_cmd;

	if (alloc_cmd(&ret_cmd))
		return (NULL);
	current_cmd = ret_cmd;	
	while ((*token_stream)->type != END && (*token_stream)->type != PIPE_OPERATOR)
	{
		current_cmd->cmd_prefix = parse_io_redir(token_stream);
		if (!current_cmd->cmd_prefix)
			return (NULL);

		// Meter tokens en el campo cmd hasta que el siguiente token != COMMAND
		while ((*token_stream)->type == COMMAND)
		{
			if (append_darray(&current_cmd->cmd, parse_word(token_stream)->text))
				return (NULL);
			// append_darray(&current_cmd->cmd, (*token_stream)->text);
			// (*token_stream)++;
		}
		if (append_darray(&current_cmd->cmd, NULL)) //NULL para el terminación y el último para el execve
			return (NULL);

		// Parseo de redirecciones.
		current_cmd->cmd_suffix = parse_io_redir(token_stream);
		if (!current_cmd->cmd_suffix)
			return (NULL);

		// Parsing next command.
		if (alloc_cmd(&tmp_cmd))
			return (NULL);
		current_cmd = tmp_cmd;
	}
	current_cmd->next = NULL;
	return (ret_cmd);
}
