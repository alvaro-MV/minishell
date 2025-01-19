/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:08:46 by alvmoral          #+#    #+#             */
/*   Updated: 2025/01/18 18:27:47 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DICTIONARY_H
# define DICTIONARY_H

# include <stdlib.h>
#include "../libft/include/libft.h"
#include "../libft/include/get_next_line.h"
# include <stdint.h>
# include <string.h>

# define FNV_OFFSET 2166136261
# define FNV_PRIME 16777619
# define INITIAL_CAPACITY 16

typedef struct s_t_dic_entry
{
	char	*key;
	char	*value;
}			t_dic_entry;

typedef struct dict
{
	t_dic_entry		**entries;
	unsigned int	n_elements;
	unsigned int	capacity;
}					t_dictionary;

t_dictionary	*dict_init(int capacity);
void			dict_insert(t_dictionary **dic_p, t_dic_entry *entry);
int				dict_expand(t_dictionary **dic_pointer);
char			*dict_get(t_dictionary *dic, char *key);
unsigned int	dict_hash(char *key);
void			dict_delete(t_dictionary *dic);
t_dic_entry		*dict_create_entry(char *key, char *value);

#endif