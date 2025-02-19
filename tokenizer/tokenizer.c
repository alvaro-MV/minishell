#include "tokenizer.h"

size_t	count_n_tokens(char *line)
{
	int	i;
	int	inside_quote;
	size_t	n_op;

	i = 0;
	n_op = 0;
	inside_quote = 0;
	while (line[i])
	{
		traverse_quote(line, &i);
		if (is_simple_operator(line[i]))
		{
			if (is_double_operator(line[i + 1]))
				i++;
			n_op++;
			while (isspace(line[i + 1]))
				i++;
			i++;
			continue ;
		}
		else if (isspace(line[i]))
		{
			while (isspace(line[i]))
				i++;
			if (line[i] != '\0')
				n_op++;
			i--;
		}
		i++;
	}
	return (++n_op);
}

int	add_token(t_darray **token_stream, char *text)
{
	t_token	token_entry;
	t_token	*last_token;
	
	token_entry.text = text;
	last_token = ((t_token *) r_darray(*token_stream, -1));
	if (!text)
		token_entry.type = END;
	else if (is_double_operator(text[0]))
		token_entry.type = IO_OPERATOR;
	else if (ft_printf("last_token: %d", last_token->type) && (*token_stream)->full_idx > 0 && last_token->type == IO_OPERATOR)
		token_entry.type = FILENAME;
	else if (text[0] == '|')
		token_entry.type = PIPE_OPERATOR;
	else
		token_entry.type = COMMAND;
	if (!append_darray(token_stream, &token_entry))
		return (free(text), 0);
	return (1);
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

t_token	*tokenizer(char *line)
{
	int			i;
	int			start;
	t_darray	*tokens_darray;
	t_token		*tokens;

	i = 0;
	start = 0;
	tokens_darray = alloc_darray(count_n_tokens(line) * 2 + 5, sizeof(t_token)); //5 es aleatorio
	if (!tokens_darray)
		return (NULL);
	while (tokens_darray->full_idx < count_n_tokens(line))
	{
		traverse_quote(line, &i);
		if (is_simple_operator(line[i]))
		{
			if (!tokenize_operator(line, &i, &start, &tokens_darray))
				return (NULL);
			continue ;
		}
		else if (isspace(line[i]) || !line[i])
		{
			if (!tokenize_literal(line, &i, &start, &tokens_darray))
				return (NULL);
		}
		i++;
	}
	add_token(&tokens_darray, NULL);
	tokens = (t_token *) tokens_darray->darray;
	free(tokens_darray);
	return (tokens);
}

// int	main(int argc, char **argv)
// {
// 	int			i;
// 	char		*line;
// 	t_token		*token_stream;
	
// 	ft_printf("\n");
// 	line = "echo adios | echo adios | echo adios | echo adios";
// 	token_stream = tokenizer(line);
// 	i = 0;
// 	while (token_stream && token_stream[i].type != END)
// 	{
// 		printf("token: %s -|- type: %d\n", token_stream[i].text, token_stream[i].type);
// 		i++;
// 	}
// 	free_tokens(token_stream);
// }

/*  ******************  [[Testeo]]	***********************  */
/*  ******************  [[Testeo]]	***********************  */
/*  ******************  [[Testeo]]	***********************  */

t_token	*tester_token(char *line)
{
	int			i;
	t_token		*token_stream;
	
	ft_printf("\n");
	token_stream = tokenizer(line);
	i = 0;
	while (token_stream && token_stream[i].type != END)
	{
		printf("token: %s -|- type: %d\n", token_stream[i].text, token_stream[i].type);
		i++;
	}
	return (token_stream);
}

void	intr_token_expect(t_token **expected, int idx, char *text, token_type type)
{
	(*expected)[idx].text = text;
	(*expected)[idx].type = type;
}

int	compare_token_arr(t_token *actual, t_token *expected, int len)
{
	int	i = 0;
	while (i < len)
	{
		if (!actual[i].text)
			return (0);
		if (ft_strcmp(actual[i].text, expected[i].text))
			return (0);
		if (actual[i].type != expected[i].type)
			return (0);
		i++;
	}
	return (1);
}

int	main(void)
{
	char	*line;
	int		len = 0;
	t_token	*expected = ft_calloc(1000, sizeof(t_token));
	t_token	*actual;

	line = ft_strdup("Mini chele");
	actual = tester_token(line);
	intr_token_expect(&expected, 0, "Mini", 4);
	len++;
	intr_token_expect(&expected, 1, "chele", 4);
	len++;
	if (compare_token_arr(actual, expected, len))
		ft_printf("\033[32m%l[OK]\n\033[0m");
	else
		ft_printf("\033[31m%l[KO]\n\033[0m");
	free_tokens(actual);
	free(line);

	len = 0;
	line = ft_strdup("ls | cat -e > outfile");
	actual = tester_token(line);
	intr_token_expect(&expected, 0, "ls", 4);
	len++;
	intr_token_expect(&expected, 1, "|", 2);
	len++;
	intr_token_expect(&expected, 1, "cat", 4);
	len++;
	intr_token_expect(&expected, 1, "-e", 4);
	len++;
	intr_token_expect(&expected, 1, ">", 1);
	len++;
	intr_token_expect(&expected, 1, "outfile", 3);
	len++;
	if (compare_token_arr(actual, expected, len))
		ft_printf("\033[32m%l[OK]\n\033[0m");
	else
		ft_printf("\033[31m%l[KO]\n\033[0m");
	free_tokens(actual);
	free(line);
}

// int main(int argc, char **argv)
// {
//     char		*line;
// 	int			i;
// 	t_token		*token_stream;
	
// 	line  = argv[1];
// 	while (line = readline("\032[32mminishell\033[0m$ "))
// 	{
// 		ft_printf("\n");
// 		add_history(line);
// 		token_stream = tokenizer(line);
// 		i = 0;
// 		while (token_stream && token_stream[i].type != END)
// 		{
// 			printf("token: %s -|- type: %d\n", token_stream[i].text, token_stream[i].type);
// 			i++;
// 		}
// 		free_tokens(token_stream);
// 		free(line);
// 	}
// 	rl_clear_history();
// 	return 0;
// }

/* 		---------------- [Test] ----------------      */
/* 

	ft_printf("%d\n", count_n_tokens("\"Hola que tal \' ls Me vengo\" \'"));
	ft_printf("%d\n", count_n_tokens("\"Hola que tal \' ls Me vengo\"\'"));
	Putting | <out fire >with_gasoline

 */