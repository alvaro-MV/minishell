/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:50:22 by alvmoral          #+#    #+#             */
/*   Updated: 2025/05/19 13:45:36 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	static int	inside_quote = 0;

	if (c == quote)
	{
		inside_quote = 1 - inside_quote;
		if (!inside_quote)
			return (0);
		return (1);
	}
	if (c == '\0')
		inside_quote = 0;
	if (inside_quote == 1)
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
