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

int	is_quote(char argv_char)
{
	if (argv_char == '\'')
		return (1);
	else if (argv_char == '\"')
		return (1);
	else
		return (0);
}

int	add_token(t_darray **tokens, char *element)
{
	if (!append_darray(tokens, &element))
		return (0);
	return (1);
}

