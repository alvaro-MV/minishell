#include "parser.h"

int	alloc_io_redir(t_io_redir **ptr__io_redir)
{
	*ptr__io_redir = ft_calloc(1, sizeof(t_io_redir));
	if (!*ptr__io_redir)
		return (0);
	return (1);
}

t_io_redir	*parse_io_redir(t_token **token_stream)
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
			ft_printf("minishell: syntax error near unexpected token ");
			if ((*token_stream)->type == END)
				ft_printf("`newline'\n");
			else
				ft_printf("%s\n", (*token_stream)->text);
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
