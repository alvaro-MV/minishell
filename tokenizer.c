#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <editline/readline.h>
#include <readline/history.h>
#include "dynamic_array.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	init;

	if (start > strlen(s))
		len = 0;
	else if (len > strlen(s) - start)
		len = strlen(s) - start;
	ptr = (char *) calloc(len + 1, sizeof(char));
	if (ptr == NULL)
		return (NULL);
	init = 0;
	while (s[init] && len--)
	{
		ptr[init++] = s[start++];
	}
	ptr[init] = ""[0];
	return (ptr);
}

void    ft_free_array(char **marr)
{
	char			*free_ptr;
	unsigned int	i;

	i = 0;
	if (marr == NULL)
		return ;
	while (marr[i])
	{
		free_ptr = marr[i];
		i++;
		free(free_ptr);
	}
	free(marr);
}

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

int	is_doble_operator(char argv_char)
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
			if (is_doble_operator(argv[i + 1]))
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

t_darray	*tokenizer_guarro(char *argv)
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
			if (is_doble_operator(argv[i]) && is_doble_operator(argv[i + 1]))
				len_op++;
			if (!add_token(&tokens, ft_substr(argv, i, len_op)))
				return (free_darray(tokens), NULL);
			if (is_doble_operator(argv[i]) && is_doble_operator(argv[i + 1]))
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

int main(int argc, char **argv)
{
    char		*line;
	int			i;
	t_darray	*tokens;
	char		**token_list;
	
	// if (argc != 2)
	// 	return (write(1, "./a.out \"<sequence>\"\n", 22));
	// argv++;
	// tokens = tokenizer_guarro(argv[0]);
	// token_list = (char **) tokens->darray;
	// i = 0;
	// printf("full_idx: %zu\n", tokens->full_idx);
	// while (i < tokens->full_idx)
	// {
	// 	printf("token: %s\n", token_list[i]);
	// 	i++;
	// }
	// ft_free_array(token_list);
	// free(tokens);
	while ((line = readline("> ")))
	{
		printf("La línea ingresada es: %s\n", line);
		add_history(line);
		tokens = tokenizer_guarro(line);
		token_list = (char **) tokens->darray;
		i = 0;
		while (i < tokens->full_idx)
		{
			printf("token: %s\n", token_list[i]);
			i++;
		}
		ft_free_array(token_list);
		free(tokens);
		free(line);
	}
	rl_clear_history();
    return 0;
}