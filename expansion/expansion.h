/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:16:06 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/14 20:40:19 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "../data_structs/dictionary.h"
# include "../libft/include/libft.h"

typedef enum expand_states
{
	WORD = 1,
	DOUBLE_QUOTE,
	SINGLE_QUOTE,
	ENV_VAR
}					t_expand_states;

typedef struct utils
{
	int				i;
	t_expand_states	state;
	t_expand_states	old_state;
	int				len_env_var;
	char			*expanded_str;
}					t_utils;

void				insert_special_params(t_dictionary **env);
char				*expand_str(char *str, t_dictionary *env);
int					is_env_var(char *str, t_utils utils);
int					is_for_expand_str(char *str);
void				join_char(char **expanded_str, char *str);
int					is_special_var(char *var);

#endif