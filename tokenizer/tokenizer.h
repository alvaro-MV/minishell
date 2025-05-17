/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:22:20 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/17 10:38:51 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../data_structs/dynamic_array.h"
# include "../libft/include/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef enum token_type
{
	IO_OPERATOR = 1,
	PIPE_OPERATOR,
	FILENAME,
	COMMAND,
	END
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*text;
}					t_token;

char				*handle_fin_quotes(char *line, char quote);
void				process_quotes(const char *str, bool *in_single_quote,
						bool *in_double_quote);
char				unclosed_quote_char(const char *str);
int					is_simple_operator(char argv_char);
int					is_double_operator(char argv_char);
int					still_in_quote(char c, char quote);
int					add_token(t_darray **tokens, char *element);
void				free_tokens(t_token *tokens);
void				process_operator(char *argv, int *i, size_t *n_op);
void				process_whitespace(char *argv, int *i, size_t *n_op);
size_t				count_n_tokens(char *argv);
int					tokenize_operator(char *line, int *i, int *start,
						t_darray **tokens);
int					tokenize_literal(char *line, int *i, int *start,
						t_darray **tokens);
int					process_tokenization(char *line, t_darray *tokens);
t_darray			*tokenizer_str(char *line);
t_token				*tokenizer_t_tokens(char **tokens_strings, size_t len);

#endif