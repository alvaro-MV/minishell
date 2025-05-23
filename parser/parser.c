/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:48:27 by alvmoral          #+#    #+#             */
/*   Updated: 2025/05/23 12:50:30 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*parse_word(t_token **token_stream)
{
	t_token	*ret_token;

	if ((*token_stream)->type != FILENAME && (*token_stream)->type != END)
		return (NULL);
	ret_token = ft_calloc(1, sizeof(t_token));
	ret_token->text = ft_strdup((*token_stream)->text);
	ret_token->type = (*token_stream)->type;
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
	free(element);
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
	char	unclosed;

	(void)exp;
	unclosed = '\0';
	if (element)
		unclosed = unclosed_quote_char(element);
	if (unclosed)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
		ft_putstr_fd("`", 2);
		(ft_putstr_fd(&unclosed, 2), ft_putstr_fd("'\n", 2));
		(free(element), storage_signal(2, 1));
		return (0);
	}
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
