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

t_darray	*tokenizer_str(char *argv)
{
	int			i;
	int			inside_quote;
	int			len_op;
	int			start;
	t_darray	*tokens;

	i = 0;
	start = 0;
	inside_quote = 0;
	tokens = alloc_darray(count_n_tokens(argv) + 1, sizeof(char *));
	if (!tokens)
		return (NULL);
	while (argv[i])
	{
		len_op = 1;
		while (still_in_quote(argv[i], '\''))
			i++;
		while (still_in_quote(argv[i], '\"'))
			i++;
		if (is_simple_operator(argv[i]))
		{
			if (i != 0 && !isspace(argv[i - 1]) && !is_simple_operator(argv[i - 1]))
			{
				if (!add_token(&tokens, ft_substr(argv, start, i - start)))
					return (free_darray(tokens), NULL);
			}
			if (is_double_operator(argv[i]) && is_double_operator(argv[i + 1]))
				len_op++;
			if (!add_token(&tokens, ft_substr(argv, i, len_op)))
				return (free_darray(tokens), NULL);
			if (is_double_operator(argv[i]) && is_double_operator(argv[i + 1]))
				i++;
			while (isspace(argv[i + 1]) && argv[i + 1] != '\0')
				i++;
			i++;
			start = i;
			continue ;
		}
		else if (isspace(argv[i]))
		{
			if (!add_token(&tokens, ft_substr(argv, start, i - start)))
				return (free_darray(tokens), NULL);
			while (isspace(argv[i]))
				i++;
			start = i;
			i--;
		}
		i++;
	}
	if (start != i)
	{
		if (!add_token(&tokens, ft_substr(argv, start, i - start)))
			return (free_darray(tokens), NULL);
	}
	add_token(&tokens, NULL);
	return (tokens);
}

t_token	*tokenizer(char **tokens_strings, size_t len)
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
// 		while (token_stream[i].type != end)
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
/* 		---------------- [Test] ----------------      */
/* 		---------------- [Test] ----------------      */


t_token	*tester_token(char *line)
{
	int			i;
	t_darray	*tokens_array;
	char		**tokens_strings;
	t_token		*token_stream;
	
	ft_printf("\n");
	tokens_array = tokenizer_str(line);
	tokens_strings = (char **) tokens_array->darray;
	token_stream = tokenizer(tokens_strings, tokens_array->full_idx);
	free(tokens_array);
	
	i = 0;
	while (token_stream[i].type != END)
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

typedef struct s_test {
    char *input;
    char **expected_values;
    token_type *expected_types;
    size_t length;
} t_test;

int	compare_token_arr(t_token *actual, t_test expected, int len)
{
	int	i = 0;
	while (i < len)
	{
		if (!actual[i].text)
			return (0);
		if (ft_strcmp(actual[i].text, expected.expected_values[i]))
			return (0);
		if (actual[i].type != expected.expected_types[i])
			return (0);
		i++;
	}
	return (1);
}



int	main(void)
{
	t_token	*actual;
	int		i = 0;

	t_test tests[] = {
			{
				.input = "Mini chele",
				.expected_values = (char*[]){"Mini", "chele"},
				.expected_types = (token_type[]){COMMAND, COMMAND},
				.length = 2
			},
			{
				.input = "ls | cat -e > outfile",
				.expected_values = (char*[]){"ls", "|", "cat", "-e", ">", "outfile"},
				.expected_types = (token_type[]){
					COMMAND, PIPE_OPERATOR, COMMAND, COMMAND,
					IO_OPERATOR, FILENAME
				},
				.length = 6
			}
	};
	while (i < 2)
	{
		actual = tester_token(tests[i].input);
		if (compare_token_arr(actual, tests[i], tests[i].length))
			ft_printf("\033[32m%l[OK]\n\033[0m");
		else
			ft_printf("\033[31m%l[KO]\n\033[0m");
		free_tokens(actual);
		i++;
	}

}
