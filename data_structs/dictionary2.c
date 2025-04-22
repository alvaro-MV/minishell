/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:09:28 by alvmoral          #+#    #+#             */
/*   Updated: 2025/04/22 10:29:14 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dictionary.h"
#include <stdio.h>

char	*dict_get(t_dictionary *dic, char *key)
{
	unsigned int	index;
	unsigned int	counter;

	if (key == NULL)
		return (NULL);
	index = dict_hash(key) % dic->capacity;
	counter = 0;
	while (counter < dic->capacity - 1)
	{
		if (dic->entries[index] && !strcmp(dic->entries[index]->key, key))
			return (dic->entries[index]->value);
		index++;
		if (index == dic->capacity - 1)
			index = 0;
		counter++;
	}
	return (NULL);
}

void	dict_delete(t_dictionary *dic)
{
	unsigned int	i;

	i = 0;
	while (i < dic->capacity)
	{
		if (dic->entries[i] != NULL)
		{
			free(dic->entries[i]->key);
			free(dic->entries[i]->value);
			free(dic->entries[i]);
		}
		i++;
	}
	free(dic->entries);
	free(dic);
}

t_dic_entry	*dict_create_entry(char *key, char *value)
{
	t_dic_entry	*ret_entry;

	ret_entry = malloc(sizeof(t_dic_entry));
	if (!ret_entry)
		return (NULL);
	ret_entry->key = key;
	ret_entry->value = value;
	return (ret_entry);
}

void	dict_delete_key(t_dictionary *dict, char *key)
{
	unsigned int	index;
	unsigned int	counter;

	if (key == NULL)
		write(1, "", 0);
	index = dict_hash(key) % dict->capacity;
	counter = 0;
	while (counter < dict->capacity - 1)
	{
		if (dict->entries[index] && !strcmp(dict->entries[index]->key, key))
		{
			free(dict->entries[index]);
			dict->entries[index] = NULL;
			return ;
		}
		index++;
		if (index == dict->capacity - 1)
			index = 0;
		counter++;
	}
}

char	**dict_get_keys(t_dictionary *dict)
{
	unsigned int	counter;
	char			**ret;
	char			**tmp;
	
	ret = malloc((dict->capacity + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	tmp = ret;
	counter = 0;
	while (counter < dict->capacity - 1)
	{
		if (dict->entries[counter])
		{
			*tmp = dict->entries[counter]->key;
			tmp++;
		}
		counter++;
	}
	*tmp = NULL;
	return (ret);
}

// int	main(int argc, char **argv, char **env)
// {

// 	t_dictionary *dict = dict_init(5);
// 	char *path = ft_strdup("PATH");
// 	char *path_value = ft_strdup("bin:/usr/bin");
// 	t_dic_entry *entry = dict_create_entry(path, path_value);
// 	if (!entry)
// 		return (dict_delete(dict), 1);
// 	dict_insert(&dict, entry);
// 	printf("PATH=%s\n", dict_get(dict, "PATH"));
	
	
// 	entry = dict_create_entry(ft_strdup("PATH"), ft_strdup("home/wachowsky:perico"));
	
// 	dict_insert(&dict, entry);
// 	printf("PATH=%s\n", dict_get(dict, "PATH"));

// 	dict_delete(dict);
// }