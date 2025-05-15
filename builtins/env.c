/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:58:02 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/15 16:17:30 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	is_exportable_var(t_dictionary *dic, char *key)
{
	unsigned int	index;
	unsigned int	counter;

	if (key == NULL)
		return (0);
	index = dict_hash(key) % dic->capacity;
	counter = 0;
	while (counter < dic->capacity - 1)
	{
		if (dic->entries[index] && !ft_strcmp(dic->entries[index]->key, key))
			return (dic->entries[index]->export);
		index++;
		if (index == dic->capacity - 1)
			index = 0;
		counter++;
	}
	return (0);
}

int	ft_env(char **args, t_exec *exec)
{
	char	**env_keys;

	env_keys = dict_get_keys(exec->env);
	if (args[0] && args[1] == NULL)
	{
		while (*env_keys != NULL)
		{
			if (is_exportable_var(exec->env, *env_keys))
				ft_printf("%s=%s\n", *env_keys, dict_get(exec->env, *env_keys));
			env_keys++;
		}
	}
	else
	{
		ft_putstr_fd("minishell: env: too much arguments\n", 2);
		return (1);
	}
	return (0);
}
