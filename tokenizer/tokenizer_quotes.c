/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:51:57 by alvmoral          #+#    #+#             */
/*   Updated: 2025/05/18 16:06:38 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

char	*handle_fin_quotes(char *line, char quote)
{
	t_darray	*darr;
	char		*tmp;
	char		*quote_line;
	int			i;

	if (quote == '\0')
		return (ft_strdup(line));
	quote_line = NULL;
	darr = alloc_darray(10, sizeof(char));
	append_darray(&darr, "\n");
	while (1)
	{
		while(!quote_line)
			quote_line = readline("quote> ");
		i = 0;
		while (quote_line[i])
			append_darray(&darr, &quote_line[i++]);
		append_darray(&darr, "\n");
		if (ft_strchr(quote_line, quote))
			break ;
		free(quote_line);
		quote_line = NULL;
	}
	tmp = ft_strjoin(line, (char *)darr->darray);
	return (free(quote_line), free_darray(darr), tmp);
}

void	process_quotes(const char *str, bool *in_single_quote,
		bool *in_double_quote)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\\')
		{
			if (str[i + 1] != '\0')
			{
				i += 2;
				continue ;
			}
		}
		else if (str[i] == '\'' && !(*in_double_quote))
			*in_single_quote = !(*in_single_quote);
		else if (str[i] == '"' && !(*in_single_quote))
			*in_double_quote = !(*in_double_quote);
		i++;
	}
}

char	unclosed_quote_char(const char *str)
{
	bool	in_single_quote;
	bool	in_double_quote;

	in_single_quote = false;
	in_double_quote = false;
	process_quotes(str, &in_single_quote, &in_double_quote);
	if (in_single_quote)
		return ('\'');
	if (in_double_quote)
		return ('"');
	return ('\0');
}
