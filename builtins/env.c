/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:58:02 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/26 21:06:29 by lvez-dia         ###   ########.fr       */
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

static void	print_env_var(t_dictionary *env, char *name)
{
	char	*value;

	if (!is_exportable_var(env, name))
		return ;
	value = dict_get(env, name);
	if (value == NULL)
		ft_printf("%s=\n", name);
	else
		ft_printf("%s=%s\n", name, value);
}

int	ft_env(char **args, t_exec *exec)
{
	char	**env_keys;
	char	**tmp;

	env_keys = dict_get_keys(exec->env);
	tmp = env_keys;
	if (args[0] && args[1] == NULL)
	{
		while (*env_keys != NULL)
		{
			print_env_var(exec->env, *env_keys);
			env_keys++;
		}
	}
	else
	{
		ft_putstr_fd("minishell: env: too much arguments\n", 2);
		ft_free_array(tmp);
		return (1);
	}
	ft_free_array(tmp);
	return (0);
}
