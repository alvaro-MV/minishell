/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:58:43 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/15 13:44:02 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	remove_env_var(t_exec *exec, char *var_name)
{
	int	j;
	int	k;

	j = 0;
	while (exec->main_env[j])
	{
		if (!ft_strncmp(exec->main_env[j], var_name, ft_strlen(var_name))
			&& exec->main_env[j][ft_strlen(var_name)] == '=')
		{
			k = j;
			while (exec->main_env[k])
			{
				exec->main_env[k] = exec->main_env[k + 1];
				k++;
			}
			exec->main_env[k] = NULL;
			dict_delete_key(exec->env, var_name);
			break ;
		}
		j++;
	}
}

int	unset(t_exec *exec, char **arg)
{
	int	i;

	i = 1;
	if (!arg[1])
		return (0);
	if (!exec->main_env || exec->main_env[0] == NULL)
		return (0);
	while (arg[i])
	{
		if (!is_valid_name(arg[i]))
		{
			export_error(arg[i]);
			i++;
			continue ;
		}
		remove_env_var(exec, arg[i]);
		i++;
	}
	return (0);
}
