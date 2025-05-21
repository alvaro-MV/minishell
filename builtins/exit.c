/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:58:16 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/21 23:45:51 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	free_at_exit(t_exec *exec_vars)
{
	close_cmd_fds(exec_vars->cmd);
	dict_delete(exec_vars->env);
	free_ast(exec_vars->mini->sequence);
	free(exec_vars->mini->pids);
	close(exec_vars->mini->saved_std[0]);
	close(exec_vars->mini->saved_std[1]);
}

int	ft_exit(t_exec *exec, char **args)
{
	int	status;

	rl_clear_history();
	if (!args[1])
		(ft_free_array(args), free_at_exit(exec), exit(0));
	if (!is_numeric(args[1]))
	{
		ft_printf("exit\n");
		ft_printf("exit: %s: numeric argument required\n", args[1]);
		free_at_exit(exec);
		exit(2);
	}
	if (args[2])
	{
		ft_printf("exit: too many arguments\n");
		return (1);
	}
	status = ft_atoi(args[1]);
	free_at_exit(exec);
	(ft_free_array(args), exit (status % 256));
}
