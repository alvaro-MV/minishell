#include "parser.h"

void	print_AST(t_cmd_pipe *sequence); //testeo

t_token	*parse_word(t_token **token_stream)
{
	t_token	*ret_token;

	ret_token = (*token_stream);
	if ((*token_stream)->type != END)
		(*token_stream)++;
	return (ret_token);
}

t_io_redir	*parse_io_redir(t_token **token_stream)
{
	t_io_redir	*ret_io_redir;
	t_io_redir	*current_io_redir;
	t_io_redir	*tmp_io_redir;

	ret_io_redir = ft_calloc(1, sizeof(t_io_redir));
	if (!ret_io_redir)
		return (NULL); //Por determinar. Lo suyo sería liberar todo el AST.
	current_io_redir = ret_io_redir;
	while ((*token_stream)->type == IO_OPERATOR)
	{
		current_io_redir->op = parse_word(token_stream);
		current_io_redir->filename = parse_word(token_stream);
		tmp_io_redir = malloc(sizeof(t_io_redir));
		if (!tmp_io_redir)
			return (NULL); //Por determinar. Lo suyo sería liberar todo el AST.
		current_io_redir->next = tmp_io_redir;
		current_io_redir = tmp_io_redir;
	}
	current_io_redir->next = NULL;
	return (ret_io_redir);
}

t_cmd	*parse_cmd(t_token **token_stream)
{
	t_cmd	*ret_cmd;
	t_cmd	*tmp_cmd;
	t_cmd	*current_cmd;

	ret_cmd = ft_calloc(1, sizeof(t_cmd));
	if (!ret_cmd)
		return (NULL);
	ret_cmd->cmd = alloc_darray(2, sizeof(char *));
	current_cmd = ret_cmd;	
	while ((*token_stream)->type != END && (*token_stream)->type != PIPE_OPERATOR)
	{
		current_cmd->cmd_prefix = parse_io_redir(token_stream);
		while ((*token_stream)->type == COMMAND)
		{
			add_token(&current_cmd->cmd, (*token_stream)->text);
			(*token_stream)++;
		}
		add_token(&current_cmd->cmd, NULL);
		current_cmd->cmd_suffix = parse_io_redir(token_stream);
		
		tmp_cmd = malloc(sizeof(t_cmd));
		if (!tmp_cmd)
			return (NULL); //Se tiene que liberar todo el AST
		current_cmd->next = tmp_cmd;
		tmp_cmd->cmd = alloc_darray(2, sizeof(char *));
		current_cmd = tmp_cmd;
	}
	current_cmd->next = NULL;
	return (ret_cmd);
}

t_cmd_pipe	*parse_cmd_pipe(t_token **token_stream)
{
	t_cmd_pipe	*ret_cmd_pipe;
	t_cmd_pipe	*current_cmd_pipe;
	t_cmd_pipe	*tmp_cmd_pipe;

	ret_cmd_pipe = ft_calloc(1, sizeof(t_cmd_pipe));
	if (!ret_cmd_pipe)
		return (NULL); //Por determinar. Lo suyo sería liberar todo el AST.
	ret_cmd_pipe->cmd = parse_cmd(token_stream);
	current_cmd_pipe = ret_cmd_pipe;
	while ((*token_stream)->type == PIPE_OPERATOR)
	{
		(*token_stream)++;
		tmp_cmd_pipe = malloc(sizeof(t_cmd_pipe));
		if (!tmp_cmd_pipe)
			return (NULL); //Por determinar. Lo suyo sería liberar todo el AST.
		tmp_cmd_pipe->cmd = parse_cmd(token_stream);
		current_cmd_pipe->pipe_seq = tmp_cmd_pipe;
		current_cmd_pipe = tmp_cmd_pipe;
	}
	current_cmd_pipe->pipe_seq = NULL;
	return (ret_cmd_pipe);
}

int main(int argc, char **argv)
{
    char		*line;
	int			i;
	t_darray	*tokens_array;
	char		**tokens_strings;
	t_token		*token_stream;
	
	// while (line = readline("\033[32mminishell\033[0m$ "))
	// {
	// add_history(line);
	// tokens_array = tokenizer_str(line);
	tokens_array = tokenizer_str(argv[1]);
	tokens_strings = (char **) tokens_array->darray;
	token_stream = tokenizer_t_tokens(tokens_strings, tokens_array->full_idx);
	free(tokens_array);

	t_token	*tokens_for_free = token_stream;

	t_cmd_pipe	*sequence = parse_cmd_pipe(&token_stream);
	print_AST(sequence);
	ft_printf("\n\n");
	
	ft_free_array(tokens_strings);
	free(tokens_for_free);
	// free(line);
	// }
	// 	rl_clear_history();
		return 0;
}
