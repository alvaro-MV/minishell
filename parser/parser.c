/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:48:27 by alvmoral          #+#    #+#             */
/*   Updated: 2025/05/16 17:01:33 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	handle_expansion(t_command **cmd, char *element, t_dictionary *env)
{
	char	**split;
	char	*expanded_cmd;
	char	*append_arg;
	int		i;

	expanded_cmd = expand_str(element, env);
	if (!expanded_cmd)
		return (0);
	split = ft_split(expanded_cmd, ' ');
	if (!split)
		return (free(expanded_cmd), 0);
	i = -1;
	while (split[++i])
	{
		append_arg = ft_strdup(split[i]);
		if (!append_darray(cmd, &append_arg))
			return (free(expanded_cmd), ft_free_array(split), 0);
	}
	(free(expanded_cmd), ft_free_array(split));
	return (1);
}

int	add_command(t_command **cmd, char *element, t_dictionary *env, int exp)
{
	(void)exp;
	if (!element || (element && element[0] != '$') || (element
			&& element[0] == '$' && exp))
	{
		if (!append_darray(cmd, &element))
			return (0);
		return (1);
	}
	return (handle_expansion(cmd, element, env));
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
