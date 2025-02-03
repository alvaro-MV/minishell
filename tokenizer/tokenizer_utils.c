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

int	still_in_quote(char c, char quote)
{
	static int inside_quote = 0;

	if (c == quote)
	{
		inside_quote = 1 - inside_quote;
		return (1);
	}
	if (inside_quote == 1)
		return (1);
	else
		return (0);
}

void	traverse_quote(char *line, int *i)
{
	int	idx;

	idx = *i;
	while (still_in_quote(line[idx], '\''))
		idx++;
	while (still_in_quote(line[idx], '\"'))
		idx++;
	*i = idx;
}

void	free_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i].type != END)
	{
		free(tokens[i].text);
		i++;
	}
	free(tokens);
}
