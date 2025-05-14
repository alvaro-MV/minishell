/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:16:06 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/14 18:43:04 by lvez-dia         ###   ########.fr       */
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
}		t_expand_states;

void	insert_special_params(t_dictionary **env);
char	*expand_str(char *str, t_dictionary *env);

#endif