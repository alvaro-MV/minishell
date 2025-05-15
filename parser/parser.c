#include "parser.h"

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

int	add_command(t_command **cmd, char *element, t_dictionary *env, int exp)
{
	char	**split;
	int		i;
	char	*expanded_cmd;
	char	*append_arg;

	(void)exp;
	i = -1;
	if (!element || (element && element[0] != '$') || (element
			&& element[0] == '$' && exp))
	{
		if (!append_darray(cmd, &element))
			return (0);
		return (1);
	}
	else
	{
		expanded_cmd = expand_str(element, env);
		if (!expanded_cmd)
			return (0);
		split = ft_split(expanded_cmd, ' ');
		if (!split)
			return (free(expanded_cmd), 0);
		while (split[++i])
		{
			append_arg = ft_strdup(split[i]);
			if (!append_darray(cmd, &append_arg))
				return (free(expanded_cmd), ft_free_array(split), 0);
		}
		(free(expanded_cmd), ft_free_array(split));
	}
	return (1);
}

void	print_from_diff(char *AST, char *expected)
{
	int	i;

	i = 0;
	while (AST[i] == expected[i] && AST[i] != '\0' && expected[i] != '\0')
		i++;
	ft_printf("A: %s\n", &AST[i]);
	ft_printf("e: %s\n", &expected[i]);
}
