/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:51:57 by alvmoral          #+#    #+#             */
/*   Updated: 2025/05/15 18:03:16 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

char    *handle_fin_quotes(char *line, char quote)
{
    t_darray    *darr;
    char        *tmp;
    char        *quote_line;
    int         i;

    if (quote == '\0')
        return (ft_strdup(line));
    quote_line = NULL;
    darr = alloc_darray(10, sizeof(char));
    append_darray(&darr, "\n");
    while (1)
    {
        quote_line = readline("quote> ");
        i = -1;
        while (quote_line[++i])
            append_darray(&darr, &quote_line[i]);
        append_darray(&darr, "\n");
        if (ft_strchr(quote_line, quote))
            break ;
        free(quote_line);
    }
    free(quote_line);
    tmp = line;
    tmp = ft_strjoin(tmp, (char *) darr->darray);
    return (free_darray(darr), tmp);
}

char unclosed_quote_char(const char *str)
{
    bool in_single_quote = false;
    bool in_double_quote = false;

    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '\\')
        {
            if (str[i + 1] != '\0')
            {
                i += 2;
                continue;
            }
        }
        else if (str[i] == '\'' && !in_double_quote)
            in_single_quote = !in_single_quote;
        else if (str[i] == '"' && !in_single_quote)
            in_double_quote = !in_double_quote;
        i++;
    }
    if (in_single_quote)
        return '\'';
    if (in_double_quote)
        return '"';
    return '\0';
}
