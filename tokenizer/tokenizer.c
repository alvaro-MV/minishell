#include "tokenizer.h"

size_t	count_n_tokens(char *argv)
{
	int	i;
	size_t	n_op;

	i = 0;
	n_op = 0;
	while (argv[i])
	{
		while (still_in_quote(argv[i], '\''))
			i++;
		while (still_in_quote(argv[i], '\"'))
			i++;
		if (is_simple_operator(argv[i]))
		{
			if (i && !isspace(argv[i - 1]) && !is_simple_operator(argv[i - 1]))
				n_op++;
			if (argv[i] == argv[i + 1])
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
	if (i > 0 && !is_double_operator(argv[i - 1]))
		++n_op;
	return (n_op);
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
	if (line[*i] == line[*i + 1])
		len_op++;
	if (!add_token(tokens, ft_substr(line, *i, len_op)))
		return (free_darray(*tokens), 0);
	if (line[*i] == line[*i + 1])
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
		if (tokens_strings[i][0] == '|')
			token_stream[i].type = PIPE_OPERATOR;
		else if (is_double_operator(tokens_strings[i][0]))
			token_stream[i].type = IO_OPERATOR;
		else if (i > 0 && token_stream[i - 1].type == IO_OPERATOR)
			token_stream[i].type = FILENAME;
		else
			token_stream[i].type = COMMAND;
		i++;
	}
	token_stream[i].type = END;
	token_stream[i].text = NULL;
	return (token_stream);
}

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
	token_stream = tokenizer_t_tokens(tokens_strings, tokens_array->full_idx);

	// Liberar cada string individualmente
	for (int j = 0; (size_t) j < tokens_array->full_idx; j++)
		free(tokens_strings[j]);

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

// int	main(void)
// {
// 	t_token	*actual;
// 	size_t	i = 0;

// 	t_test tests[] = {
// 		{
//  			.input = "Mini chele",
//  			.expected_values = (char*[]){"Mini", "chele"},
//  			.expected_types = (token_type[]){COMMAND, COMMAND},
//  			.length = 2
//  		},
//  		{
//  			.input = "ls | cat -e > outfile",
//  			.expected_values = (char*[]){"ls", "|", "cat", "-e", ">", "outfile"},
//  			.expected_types = (token_type[]){
//  			COMMAND, PIPE_OPERATOR, COMMAND, COMMAND,
//  			IO_OPERATOR, FILENAME
//  			},
//  			.length = 6
//  		},
//  		{
//  			.input = "ls | cat | epa",
//  			.expected_values = (char*[]){"ls", "|", "cat", "|", "epa"},
//  			.expected_types = (token_type[]){
//  			COMMAND, PIPE_OPERATOR, COMMAND, PIPE_OPERATOR, COMMAND
//  			},
//  			.length = 5
//  		},
//  		{
//  			.input = "echo '$' | cat< outfile >>> l",
//  			.expected_values = (char*[]){"echo", "'$'", "|" , "cat", "<", "outfile", ">>", ">", "l"},
//  			.expected_types = (token_type[]){
//  			COMMAND, COMMAND, PIPE_OPERATOR, COMMAND, IO_OPERATOR, FILENAME,
//  			IO_OPERATOR, IO_OPERATOR, FILENAME
//  			},
//  			.length = 9
//  		},
//  		{
//  			.input = "echo \"$ <infile | grep 00\" | cat -e",
//  			.expected_values = (char*[]){"echo", "\"$ <infile | grep 00\"", "|" , "cat", "-e"},
//  			.expected_types = (token_type[]){
//  			COMMAND, COMMAND, PIPE_OPERATOR, COMMAND, COMMAND
//  			},	
//  			.length = 5
//  		},
//  		{
//  			.input = "ls >\"./outfiles/outfile\" \"1\" \"2\" \"3\" \"4\" \"5\"",
//  			.expected_values = (char*[]){"ls", ">", "\"./outfiles/outfile\"", 
//  				"\"1\"", "\"2\"", "\"3\"", "\"4\"", "\"5\""},
//  			.expected_types = (token_type[]){COMMAND, IO_OPERATOR, FILENAME, COMMAND, COMMAND,
//  								COMMAND, COMMAND, COMMAND},
//  			.length = 8
//  		},
//  		{
//  			.input = "ls >\"./outfiles/outfile\"\"1\"\"2\"\"3\"\"4\"\"5\"",
//  			.expected_values = (char*[]){"ls", ">", 
//  				"\"./outfiles/outfile\"\"1\"\"2\"\"3\"\"4\"\"5\""},
//  			.expected_types = (token_type[]){COMMAND, IO_OPERATOR, FILENAME},
//  			.length = 3
//  		},
//  		{
//  			.input = "echo hi >./outfiles/outfile01 >./outfiles/outfile02 | echo bye",
//  			.expected_values = (char*[]){"echo", "hi", ">", "./outfiles/outfile01", 
//  				">", "./outfiles/outfile02", "|", "echo", "bye"},
//  			.expected_types = (token_type[]){COMMAND, COMMAND, IO_OPERATOR, FILENAME,
//  				IO_OPERATOR, FILENAME, PIPE_OPERATOR, COMMAND, COMMAND},
//  			.length = 9
//  		},
//  		{
//  			.input = "/bin/echo \"'\"'$USER'\"'\"",
//  			.expected_values = (char*[]){"/bin/echo", "\"'\"'$USER'\"'\""},
//  			.expected_types = (token_type[]){COMMAND, COMMAND},
//  			.length = 2
//  		},
// 		{
// 			.input = "echo hi |  \"|\"",
// 			.expected_values = (char*[]){"echo", "hi", "|", "\"|\""},
// 			.expected_types = (token_type[]){COMMAND, COMMAND, PIPE_OPERATOR, COMMAND},
// 			.length = 4
// 		},
// 		{
// 			.input = ">| echo sure",
// 			.expected_values = (char*[]){">", "|", "echo", "sure"},
// 			.expected_types = (token_type[]){IO_OPERATOR, PIPE_OPERATOR, COMMAND, COMMAND},
// 			.length = 4
// 		},
// 		{
// 			.input = "<>",
// 			.expected_values = (char*[]){"<", ">"},
// 			.expected_types = (token_type[]){IO_OPERATOR, IO_OPERATOR},
// 			.length = 2
// 		},
// 		{
// 			.input = "><",
// 			.expected_values = (char*[]){">", "<"},
// 			.expected_types = (token_type[]){IO_OPERATOR, IO_OPERATOR},
// 			.length = 2
// 		}
// 	};
// 	while (i < sizeof(tests) / sizeof(t_test))
// 	{
// 		actual = tester_token(tests[i].input);
// 		if (compare_token_arr(actual, tests[i], tests[i].length))
// 			ft_printf("\033[32m%l[OK]\n\033[0m");
// 		else
// 			ft_printf("\033[31m%l[KO]\n\033[0m");
// 		free_tokens(actual);
// 		i++;
// 	}
// 	return (0);
// }
// -> cc tokenizer/*.c data_structs/*.c libft/*.c