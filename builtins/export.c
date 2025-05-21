/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:58:23 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/21 12:59:33 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtins.h"

void	export_error(char *name)
{
	ft_printf("minishell: export: `%s': not a valid identifier\n", name);
}

int	print_exported_vars(t_exec *exec)
{
	char	**env_keys;
	char	*value_for_printing;
	int		i;

	i = -1;
	env_keys = dict_get_keys(exec->env);
	if (!env_keys)
		return (1);
	sort_strings(env_keys, exec->env->capacity);
	while (env_keys[++i])
	{
		value_for_printing = dict_get(exec->env, env_keys[i]);
		ft_printf("declare -x %s", env_keys[i]);
		if (value_for_printing != NULL)
			ft_printf("=\"%s\"", value_for_printing);
		ft_printf("\n");
	}
	return (0);
}

int	process_argument(char *argument, t_exec *exec)
{
	t_dic_entry	*entry;
	char		**var;
	char		*value;

	var = ft_split(argument, '=');
	if (!var)
		return (1);
	if (is_valid_name(var[0]))
	{
		if (var[1] == NULL && ft_strchr(argument, '='))
			value = "";
		else
			value = var[1];
		entry = dict_create_entry(ft_strdup(var[0]), ft_strdup(value));
		if (ft_strchr(argument, '='))
			entry->export = 1;
		dict_insert(&exec->env, entry);
	}
	else
		return (export_error(argument), ft_free_array(var), 1);
	ft_free_array(var);
	return (0);
}

int	export(t_exec *exec, char **arguments)
{
	int	status;
	int	i;

	status = 0;
	if (arguments[1] == NULL)
	{
		print_exported_vars(exec);
		return (0);
	}
	i = 1;
	while (arguments[i])
	{
		if (process_argument(arguments[i], exec))
			status = 1;
		i++;
	}
	return (status);
}
