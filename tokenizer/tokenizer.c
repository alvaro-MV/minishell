#include "tokenizer.h"

size_t	count_n_tokens(char *argv)
{
	int	i;
	int	inside_quote;
	size_t	n_op;

	i = 0;
	n_op = 0;
	inside_quote = 0;
	while (argv[i])
	{

		while (still_in_quote(argv[i], '\''))
			i++;
		while (still_in_quote(argv[i], '\"'))
			i++;
		if (is_simple_operator(argv[i]))
		{
			if (is_double_operator(argv[i + 1]))
				i++;
			n_op++;
			while (isspace(argv[i + 1]))
				i++;
			i++;
			continue ;
		}
		else if (isspace(argv[i]))
		{
			while (isspace(argv[i]))
				i++;
			if (argv[i] != '\0')
				n_op++;
			i--;
		}
		i++;
	}
	return (++n_op);
}

int	tokenize_operator(char *line, int *i, int *start, t_darray **tokens)
{
	int	len_op;

	len_op = 1;
	if (*i != 0 && !isspace(line[*i - 1]) && !is_simple_operator(line[*i - 1]))
	{
		if (!add_token(tokens, ft_substr(line, *start, *i - *start)))
			return (free_darray(*tokens), 0);
	}
	if (is_double_operator(line[*i]) && is_double_operator(line[*i + 1]))
		len_op++;
	if (!add_token(tokens, ft_substr(line, *i, len_op)))
		return (free_darray(*tokens), 0);
	if (is_double_operator(line[*i]) && is_double_operator(line[*i + 1]))
		*i = *i + 1;
	while (isspace(line[*i + 1]) && line[*i + 1] != '\0')
		*i = *i + 1;
	*i = *i + 1;
	*start = *i;
	return (1);
}

int	tokenize_literal(char *line, int *i, int *start, t_darray **tokens)
{
	if (!add_token(tokens, ft_substr(line, *start, *i - *start)))
		return (free_darray(*tokens), 0);
	while (isspace(line[*i]))
		*i = *i + 1;
	*start = *i;
	*i = *i - 1;
	return (1);
}

t_darray	*tokenizer_str(char *line)
{
	int			i;
	int			start;
	t_darray	*tokens;

	i = 0;
	start = 0;
	tokens = alloc_darray(count_n_tokens(line) + 1, sizeof(char *));
	if (!tokens)
		return (NULL);
	while (tokens->full_idx < count_n_tokens(line))
	{
		while (still_in_quote(line[i], '\''))
			i++;
		while (still_in_quote(line[i], '\"'))
			i++;
		if (is_simple_operator(line[i]))
		{
			if (!tokenize_operator(line, &i, &start, &tokens))
				return (NULL);
			continue ;
		}
		else if (isspace(line[i]) || !line[i])
		{
			if (!tokenize_literal(line, &i, &start, &tokens))
				return (NULL);
		}
		i++;
	}
	add_token(&tokens, NULL);
	return (tokens);
}

t_token	*tokenizer_t_tokens(char **tokens_strings, size_t len)
{
	int	i;

	i = 0;
	t_token	*token_stream = malloc((len + 1) * sizeof(t_token));
	i = 0;
	while (tokens_strings[i])
	{
		token_stream[i].text = tokens_strings[i];
		if (is_double_operator(tokens_strings[i][0]))
			token_stream[i].type = IO_OPERATOR;
		else if (i > 0 && token_stream[i - 1].type == IO_OPERATOR)
			token_stream[i].type = FILENAME;
		else if (tokens_strings[i][0] == '|')
			token_stream[i].type = PIPE_OPERATOR;
		else
			token_stream[i].type = COMMAND;
		i++;
	}
	token_stream[i].type = END;
	token_stream[i].text = NULL;
	return (token_stream);
}

// int main(int argc, char **argv)
// {
//     char		*line;
// 	int			i;
// 	t_darray	*tokens_array;
// 	char		**tokens_strings;
// 	t_token		*token_stream;
	
// 	while (line = readline("\033[32mminishell\033[0m$ "))
// 	{
// 		ft_printf("\n");
// 		add_history(line);
// 		tokens_array = tokenizer_str(line);
// 		tokens_strings = (char **) tokens_array->darray;
// 		token_stream = tokenizer_t_tokens(tokens_strings, tokens_array->full_idx);
// 		free(tokens_array);
		
// 		i = 0;
// 		while (token_stream[i].type != END)
// 		{
// 			printf("token: %s -|- type: %d\n", token_stream[i].text, token_stream[i].type);
// 			i++;
// 		}
// 		ft_free_array(tokens_strings);
// 		free(token_stream);
// 		free(line);
// 	}
// 		rl_clear_history();
// 		return 0;
// }



/* 		---------------- [Test] ----------------      */
/* 

	ft_printf("%d\n", count_n_tokens("\"Hola que tal \' ls Me vengo\" \'"));
	ft_printf("%d\n", count_n_tokens("\"Hola que tal \' ls Me vengo\"\'"));
	Putting | <out fire >with_gasoline

 */