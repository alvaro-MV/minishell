/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:50:25 by alvmoral          #+#    #+#             */
/*   Updated: 2025/05/19 11:42:43 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	process_operator(char *argv, int *i, size_t *n_op)
{
	if (*i && !isspace(argv[*i - 1]) && !is_simple_operator(argv[*i - 1]))
		(*n_op)++;
	if (argv[*i] == argv[*i + 1])
		(*i)++;
	(*n_op)++;
	while (isspace(argv[*i + 1]))
		(*i)++;
	(*i)++;
}

void	process_whitespace(char *argv, int *i, size_t *n_op)
{
	while (isspace(argv[*i]))
		(*i)++;
	if (argv[*i] != '\0')
		(*n_op)++;
	(*i)--;
}

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
		while (still_in_quote(argv[i], '"'))
			i++;
		if (is_simple_operator(argv[i]))
			process_operator(argv, &i, &n_op);
		else if (isspace(argv[i]))
			process_whitespace(argv, &i, &n_op);
		if (argv[i])
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
