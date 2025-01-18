#include "tokenizer.h"

int	is_simple_operator(char argv_char)
{
	if (argv_char == '>')
		return (1);
	else if (argv_char == '<')
		return (1);
	else if (argv_char == '|')
		return (1);
	else
		return (0);
}

int	is_double_operator(char argv_char)
{
	if (argv_char == '>')
		return (1);
	else if (argv_char == '<')
		return (1);
	else
		return (0);
}

size_t	count_n_tokens(char *argv)
{
	int	i;
	size_t	n_op;

	i = 0;
	n_op = 0;
	while (argv[i])
	{
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
			while (isspace(argv[i]) && argv[i + 1] != '\0')
				i++;
			i--;
			n_op++;
		}
		i++;
	}
	return (++n_op);
}

int	add_token(t_darray **tokens, char *element)
{
	if (!append_darray(tokens, &element))
		return (0);
	return (1);
}

t_darray	*tokenizer_str(char *argv)
{
	int			i;
	int			len_op;
	int			start;
	t_darray	*tokens;

	i = 0;
	start = 0;
	tokens = alloc_darray(count_n_tokens(argv) + 1, sizeof(char *));
	if (!tokens)
		return (NULL);
	while (argv[i])
	{
		len_op = 1;
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
			while (isspace(argv[i]) && argv[i + 1] != '\0')
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
			token_stream[i].type = OPERATOR;
		else if (i > 0 && token_stream[i - 1].type == OPERATOR)
			token_stream[i].type = FILENAME;
		else
			token_stream[i].type = COMMAND;
		i++;
	}
	token_stream[i].type = END;
	token_stream[i].text = NULL;
	return (token_stream);
}

int main(int argc, char **argv)
{
    char		*line;
	int			i;
	t_darray	*tokens_array;
	char		**tokens_strings;
	t_token		*token_stream;
	
	while ((line = readline("> ")))
	{
		printf("La línea ingresada es: %s\n", line);
		add_history(line);
		tokens_array = tokenizer_str(line);
		tokens_strings = (char **) tokens_array->darray;
		token_stream = tokenizer_t_tokens(tokens_strings, tokens_array->full_idx);
		free(tokens_array);
		
		i = 0;
		while (token_stream[i].type != END)
		{
			printf("token: %s -|- type: %d\n", token_stream[i].text, (int) token_stream[i].type);
			i++;
		}
		ft_free_array(tokens_strings);
		free(token_stream);
		free(line);
	}
		rl_clear_history();
		return 0;
}

