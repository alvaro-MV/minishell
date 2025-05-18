/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:58:43 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/18 16:06:59 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	remove_env_var(t_exec *exec, char *var_name)
{
	int		j;
	char	**env;

	env = dict_envp(exec->env);
	j = 0;
	while (env[j])
	{
		if (!ft_strncmp(env[j], var_name, ft_strlen(var_name))
			&& env[j][ft_strlen(var_name)] == '=')
		{
			dict_delete_key(exec->env, var_name);
			break ;
		}
		j++;
	}
	ft_free_array(env);
}

int	unset(t_exec *exec, char **arg)
{
	int	i;

	i = 1;
	if (!arg[1])
		return (0);
	if (!exec->env || exec->env->entries == NULL)
		return (0);
	while (arg[i])
	{
		if (!is_valid_name(arg[i]))
			export_error(arg[i]);
		else
			remove_env_var(exec, arg[i]);
		i++;
	}
	return (0);
}
