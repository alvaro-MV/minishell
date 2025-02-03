#include "parser.h"

void	print_AST(t_cmd_pipe *sequence); //testeo

t_token	*parse_word(t_token **token_stream)
{
	t_token	*ret_token;

	ret_token = (*token_stream);
	if (ret_token->type != FILENAME && ret_token->type != END)
		return (NULL);
	if ((*token_stream)->type != END)
		(*token_stream)++;
	return (ret_token);
}



int main(int argc, char **argv)
{
    char		*line;
	int			i;
	t_token		*token_stream;
	
	// while (line = readline("\033[32mminishell\033[0m$ "))
	// {
	// add_history(line);
	// tokens_array = tokenizer_str(line);
	token_stream = tokenizer(argv[1]);

	t_token	*tokens_for_free = token_stream;

	t_cmd_pipe	*sequence = parse_cmd_pipe(&token_stream);
	if (!sequence)
		return (0);
	print_AST(sequence);
	ft_printf("\n\n");
	
	free_AST(sequence);
	free(tokens_for_free);
	// free(line);
	// }
	// 	rl_clear_history();
		return 0;
}
