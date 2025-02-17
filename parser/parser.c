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

int	add_command(command **cmd, char *element)
{
	if (!append_darray(cmd, &element))
		return (0);
	return (1);
}

int main(int argc, char **argv)
{
    char		*line;
	int			i = 0;
	t_token		*token_stream;
	
	// while (line = readline("\033[32mminishell\033[0m$ "))
		line = argv[1];
	// {
	// 	add_history(line);
		token_stream = tokenizer(line);

		t_token	*tokens_for_free = token_stream;

		while (token_stream && token_stream[i].type != END)
		{
			printf("token: %s -|- type: %d\n", token_stream[i].text, token_stream[i].type);
			i++;
		}

		t_cmd_pipe	*sequence = parse_cmd_pipe(&token_stream);
		if (sequence)
		{
			print_AST(sequence);
			ft_printf("\n\n");
		}
		free_AST(sequence);
		free(tokens_for_free);
		// free(line);
	// }
	// rl_clear_history();
	return 0;
}
