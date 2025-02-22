#include "parser.h"

void	print_AST(t_cmd_pipe *sequence); //testeo
void	buffer_AST(t_cmd_pipe *sequence, char **AST); //testeo

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

void tester_parser(char *line, char *expected)
{
	int			i = 0;
	t_darray	*tokens_array;
	char		**tokens_strings;
	t_token		*token_stream;
	char		*AST = ft_strdup("");

	tokens_array = tokenizer_str(line);
	tokens_strings = (char **) tokens_array->darray;
	token_stream = tokenizer(tokens_strings, tokens_array->full_idx);

	t_token	*tokens_for_free = token_stream;
	t_cmd_pipe	*sequence = parse_cmd_pipe(&token_stream);
	if (sequence)
	{
		print_AST(sequence);
		buffer_AST(sequence, &AST);
		ft_printf("AST: %s\n", AST);
		ft_printf("\n\n");

		if (strcmp(AST, expected))
 			ft_printf("\033[32m%l[OK]\n\033[0m");
		else
 			ft_printf("\033[31m%l[KO]\n\033[0m");
	}

	free(AST);
	free_AST(sequence);
	free(tokens_array);
	free(tokens_for_free);
	ft_free_array(tokens_strings);
}

int	main(void)
{
	tester_parser("ls | cat", "{ ls } | \n{ cat }");
}