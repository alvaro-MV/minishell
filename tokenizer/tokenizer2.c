/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 10:01:54 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/22 23:25:10 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	process_tokenization(char *line, t_darray *tokens)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (tokens->full_idx < count_n_tokens(line))
	{
		while (still_in_quote(line[i], '\''))
			i++;
		while (still_in_quote(line[i], '\"'))
			i++;
		if (is_simple_operator(line[i]))
		{
			if (!tokenize_operator(line, &i, &start, &tokens))
				return (free(line), 0);
			continue ;
		}
		else if (isspace(line[i]) || !line[i])
		{
			if (!tokenize_literal(line, &i, &start, &tokens))
				return (free(line), 0);
		}
		i++;
	}
	add_token(&tokens, NULL);
	return (1);
}

t_darray	*tokenizer_str(char *line)
{
	char		*tmp_line;
	t_darray	*tokens;

	tmp_line = line;
	line = ft_strtrim(line, " ");
	if (!line)
		return (NULL);
	free(tmp_line);
	tokens = alloc_darray(count_n_tokens(line) + 1, sizeof(char *));
	if (!tokens)
		return (free(line), NULL);
	if (!process_tokenization(line, tokens))
		return (NULL);
	free(line);
	return (tokens);
}

t_token	*tokenizer_t_tokens(char **tokens_strings, size_t len)
{
	int		i;
	t_token	*token_stream;

	i = 0;
	token_stream = malloc((len + 1) * sizeof(t_token));
	if (!token_stream)
		return (free(token_stream), NULL);
	while (tokens_strings[i])
	{
		token_stream[i].text = ft_strdup(tokens_strings[i]);
		if (tokens_strings[i][0] == '|')
			token_stream[i].type = PIPE_OPERATOR;
		else if (is_double_operator(tokens_strings[i][0]))
			token_stream[i].type = IO_OPERATOR;
		else if (i > 0 && token_stream[i - 1].type == IO_OPERATOR)
			token_stream[i].type = FILENAME;
		else
			token_stream[i].type = COMMAND;
		i++;
	}
	token_stream[i].type = END;
	token_stream[i].text = NULL;
	return (token_stream);
}
