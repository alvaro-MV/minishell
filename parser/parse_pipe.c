#include "parser.h"

int	is_empty_cmd(t_cmd *cmd)
{
	if (cmd->cmd_prefix->op->type != END && cmd->cmd_prefix->filename->type != END)
		return (0);
	if (cmd->cmd->full_idx > 0)
		return (0);
	if (cmd->cmd_suffix->op->type != END && cmd->cmd_suffix->filename->type != END)
		return (0);
	if (cmd->next)
		return (0);
	return (1);
}

int	alloc_pipe_cmd(t_cmd_pipe **ptr_cmd_pipe)
{
	*ptr_cmd_pipe = ft_calloc(1, sizeof(t_cmd_pipe));
	if (!(*ptr_cmd_pipe))
		return (0); //Por determinar. Lo suyo sería liberar todo el AST.
	return (1);
}

t_cmd_pipe	*parse_cmd_pipe(t_token **token_stream)
{
	t_cmd_pipe	*ret_cmd_pipe;
	t_cmd_pipe	*current_cmd_pipe;
	t_cmd_pipe	*tmp_cmd_pipe;

	if (!alloc_pipe_cmd(&ret_cmd_pipe))
		return (NULL);
	ret_cmd_pipe->cmd = parse_cmd(token_stream);
	if  (!ret_cmd_pipe->cmd)
		return (free_AST(ret_cmd_pipe), NULL); //Fallo de sintaxis. Pirarse y liberar todo
	// else if (is_empty_cmd(ret_cmd_pipe->cmd))
	// 	// abrir here_doc y recibir comando: tokenización, verificación y si todo OK incuirlo en lista. 
	
	//Parsear hasta encontrar el primer comando.
	//Si falla la memoria o la verificación mediante LL (todavía no hecho),
	//entonces 
	current_cmd_pipe = ret_cmd_pipe;
	while ((*token_stream)->type == PIPE_OPERATOR) // while (parse_word(token_stream)->type == PIPE_OPERATOR)
	{
		(*token_stream)++;
		//Mismo parseo para el próximo comando.
		if (!alloc_pipe_cmd(&tmp_cmd_pipe))
			return (free_AST(ret_cmd_pipe), NULL); //Fallo de sintaxis. Pirarse y liberar todo
		tmp_cmd_pipe->cmd = parse_cmd(token_stream);
		if (!tmp_cmd_pipe->cmd)
			return (free_AST(ret_cmd_pipe), NULL); //Fallo de sintaxis. Pirarse y liberar todo
		
		//Avanzas en la lista.

		current_cmd_pipe->next = tmp_cmd_pipe;
		current_cmd_pipe = tmp_cmd_pipe;
	}
	current_cmd_pipe->next = NULL;
	return (ret_cmd_pipe);
}
