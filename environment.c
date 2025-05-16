/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:10:42 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/16 16:26:10 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**dict_envp(t_dictionary *env, unsigned int index, int j)
{
	char		**envp;
	t_dic_entry	*entry;
	char		*tmp;

	index = 0;
	j = 0;
	envp = ft_calloc(env->n_elements + 1, sizeof(char *));
	while (index < env->capacity)
	{
		if (env->entries[index])
		{
			entry = env->entries[index];
			tmp = ft_strjoin(entry->key, "=");
			envp[j] = ft_strjoin(tmp, entry->value);
			free(tmp);
			j++;
		}
		index++;
	}
	envp[j] = NULL;
	return (envp);
}

void	dict_set_env_var(t_dictionary **env, char *k, char *v, int export)
{
	t_dic_entry	*env_var;

	env_var = dict_create_entry(ft_strdup(k), ft_strdup(v));
	env_var->export = export;
	dict_insert(env, env_var);
}

void	insert_special_params(t_dictionary **env)
{
	t_dic_entry	*env_var;

	env_var = dict_create_entry(ft_strdup("@"), ft_strdup(""));
	dict_insert(env, env_var);
	env_var = dict_create_entry(ft_strdup("*"), ft_strdup(""));
	dict_insert(env, env_var);
	env_var = dict_create_entry(ft_strdup("#"), ft_strdup("0"));
	dict_insert(env, env_var);
	env_var = dict_create_entry(ft_strdup("?"), ft_strdup("0"));
	dict_insert(env, env_var);
	env_var = dict_create_entry(ft_strdup("-"), ft_strdup("himBh"));
	dict_insert(env, env_var);
	env_var = dict_create_entry(ft_strdup("$"), ft_strdup("(missing)"));
	dict_insert(env, env_var);
	env_var = dict_create_entry(ft_strdup("!"), ft_strdup("(missing)"));
	dict_insert(env, env_var);
	env_var = dict_create_entry(ft_strdup("0"), ft_strdup("minishell"));
	dict_insert(env, env_var);
}

void	process_env_variables(t_dictionary **hash_env, char **env)
{
	char	**env_var_array;
	char	*shlvl;

	while (*env)
	{
		env_var_array = ft_split(*env, '=');
		ft_strdup(env_var_array[1]);
		dict_set_env_var(hash_env, env_var_array[0], env_var_array[1], 1);
		ft_free_array(env_var_array);
		env++;
	}
	insert_special_params(hash_env);
	shlvl = dict_get(*hash_env, "SHLVL");
	if (shlvl)
	{
		shlvl = ft_itoa(ft_atoi(shlvl) + 1);
		dict_set_env_var(hash_env, "SHLVL", shlvl, 1);
		free(shlvl);
	}
}

void	get_env(t_dictionary **hash_env, char **env)
{
	char	**env_var_array;
	char	*shlvl;

	*hash_env = dict_init(230);
	if (!*env)
	{
		dict_set_env_var(hash_env, "PWD", "/home/alvaro/C42/minishell", 1);
		dict_set_env_var(hash_env, "OLDPWD", "", 1);
	}
	else
		process_env_variables(hash_env, env);
}
