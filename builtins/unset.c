/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:58:43 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/14 17:58:44 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "builtins.h"

int	unset(t_exec *exec, char **arg)
{
	int	i;
	int	j;
	int	k;

	i = 1;
	j = 0;
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
		while (exec->main_env[j])
		{
			if (!ft_strncmp(exec->main_env[j], arg[i], ft_strlen(arg[i]))
				&& exec->main_env[j][ft_strlen(arg[i])] == '=')
			{
				k = j;
				while (exec->main_env[k])
				{
					exec->main_env[k] = exec->main_env[k + 1];
					k++;
				}
				exec->main_env[k] = NULL;
				dict_delete_key(exec->env, arg[i]);
				break ;
			}
			j++;
		}
		i++;
	}
	return (0);
}
