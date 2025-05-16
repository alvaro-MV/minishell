/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:50:25 by alvmoral          #+#    #+#             */
/*   Updated: 2025/05/16 17:24:56 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

size_t	count_n_tokens(char *argv)
{
	int		i;
	size_t	n_op;

	i = 0;
	n_op = 0;
	while (argv[i])
	{
		while (still_in_quote(argv[i], '\''))
			i++;
		while (still_in_quote(argv[i], '\"'))
			i++;
		if (is_simple_operator(argv[i]))
		{
			if (i && !isspace(argv[i - 1]) && !is_simple_operator(argv[i - 1]))
				n_op++;
			if (argv[i] == argv[i + 1])
				i++;
			n_op++;
			while (isspace(argv[i + 1]))
				i++;
			i++;
			continue ;
		}
		else if (isspace(argv[i]))
		{
			while (isspace(argv[i]))
				i++;
			if (argv[i] != '\0')
				n_op++;
			i--;
		}
		i++;
	}
	if (i > 0 && !is_double_operator(argv[i - 1]))
		++n_op;
	return (n_op);
}

int	tokenize_operator(char *line, int *i, int *start, t_darray **tokens)
{
	int	len_op;

	len_op = 1;
	if (*i != 0 && !isspace(line[*i - 1]) && !is_simple_operator(line[*i - 1]))
	{
		if (!add_token(tokens, ft_substr(line, *start, *i - *start)))
			return (free_darray(*tokens), 0);
	}
	if (line[*i] == line[*i + 1])
		len_op++;
	if (!add_token(tokens, ft_substr(line, *i, len_op)))
		return (free_darray(*tokens), 0);
	if (line[*i] == line[*i + 1])
		*i = *i + 1;
	while (isspace(line[*i + 1]) && line[*i + 1] != '\0')
		*i = *i + 1;
	*i = *i + 1;
	*start = *i;
	return (1);
}

int	tokenize_literal(char *line, int *i, int *start, t_darray **tokens)
{
	if (!add_token(tokens, ft_substr(line, *start, *i - *start)))
		return (free_darray(*tokens), 0);
	while (isspace(line[*i]))
		*i = *i + 1;
	*start = *i;
	*i = *i - 1;
	return (1);
}

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
	int			i;
	int			start;
	char		*tmp_line;
	t_darray	*tokens;

	i = 0;
	start = 0;
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
	i = 0;
	while (tokens_strings[i])
	{
		token_stream[i].text = handle_fin_quotes(tokens_strings[i],
				unclosed_quote_char(tokens_strings[i]));
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
