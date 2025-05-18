/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 10:01:54 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/18 18:10:37 by alvmoral         ###   ########.fr       */
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

/*t_token	*tokenizer_t_tokens(char **tokens_strings, size_t len)
{
	int			i;
	t_token		*token_stream;
	t_io_redir	*ret_io_redir;
	t_io_redir	*current_io_redir;
	t_io_redir	*tmp_io_redir;

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
			token_st
	}
t_io_redir	*parse_io_redir(t_token * *token_stream, t_dictionary * env)
	{
		if (!alloc_io_redir(&ret_io_redir))
			return (NULL);
		current_io_redir = ret_io_redir;
		while ((*token_stream)->type == IO_OPERATOR)
		{
			current_io_redir->op = (*token_stream);
			(*token_stream)++;
			current_io_redir->filename = parse_word(token_stream);
			if (current_io_redir->filename == NULL
				|| current_io_redir->filename->type != FILENAME)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token ",
					2);
				if ((*token_stream)->type == END)
					ft_putstr_fd("`newline'\n", 2);
				else
					ft_printf("%s\n", (*token_stream)->text);
				storage_signal(2, 1);
				return (free_io_redir(ret_io_redir), NULL);
			}
			if (!ft_strcmp(current_io_redir->op->text, "<<"))
			{
				if (here_doc(current_io_redir->filename->text, current_io_redir,
						env))
					return (free_io_redir(ret_io_redir), NULL);
			}
			if (!alloc_io_redir(&tmp_io_redir))
				return (free_io_redir(ret_io_redir), NULL);
			current_io_redir->next = tmp_io_redir;
			current_io_redir = tmp_io_redir;
		}
		current_io_redir->next = NULL;
		ream[i].type = IO_OPERATOR;
		else if (i > 0 && token_stream[i
				- 1].type == IO_OPERATOR) token_stream[i].type = FILENAME;
		else token_stream[i].type = COMMAND;
		i++;
	}
	token_stream[i].type = END;
	token_stream[i].text = NULL;
	return (token_stream);
}*/
