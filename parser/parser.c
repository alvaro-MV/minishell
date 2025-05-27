/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:48:27 by alvmoral          #+#    #+#             */
/*   Updated: 2025/05/27 18:16:23 by alvmoral         ###   ########.fr       */
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
	ft_printf("expanded:-%s\n", expanded_cmd);
	if (!expanded_cmd)
		return (free(element), 0);
	if (expanded_cmd && !ft_strncmp(expanded_cmd, "", 1) && ft_strlen(element))
		return (free(element), 1);
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
	if (!element || (element && element[0] != '$'))
	{
		if (!append_darray(cmd, &element))
			return (0);
		return (1);
	}
	return (handle_expansion(cmd, element, env));
}
