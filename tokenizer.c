#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

size_t	count_n_tokens(char **argv)
{
	int	i;
	int	j;
	size_t	n_op;

	i = 0;
	j = 0;
	n_op = 0;
	while (argv[i])
	{
		while (argv[i][j])
		{
			if (is_simple_operator(argv[i][j]))
			{
				if (is_simple_operator(argv[i][j + 1]))
					j++;
				n_op++;
			}
			j++;
		}
		i++;
	}
	return (n_op);
}

int	main(int argc, char **argv, char **env)
{
	(void) argc;
	argv++;
	int		i;
	int		j;
	int		len_op;
	char	last_op;
	char	**tokens;

	i = 0;
	j = 0;
	last_op = 0;
	tokens = (char **) malloc(count_n_tokens(argv) * sizeof(char *) + 1);

	if (!tokens)
		return (1);
	while (argv[i])
	{
		while (argv[i][j])
		{
			len_op = 0;
			if (is_simple_operator(argv[i][j]))
			{
				*tokens = ft_substr(argv[i], last_op, j);
				printf("tokens: %s\n", *tokens);
				len_op++;
				if (is_simple_operator(argv[i][j + 1]))
					len_op++;
				*tokens = ft_substr(argv[i], j, len_op);
				printf("tokens: %s\n", *tokens);
				tokens++;
				if (is_simple_operator(argv[i][j + 1]))
					j++;
				last_op = j + 1;
			}
			j++;
		}
		*tokens = ft_substr(argv[i], last_op, j);
		printf("tokens: %s\n", *tokens);
		tokens++;
		i++;
	}
	return (0);
}
