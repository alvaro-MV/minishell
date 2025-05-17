/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:58:16 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/17 15:36:02 by lvez-dia         ###   ########.fr       */
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

int	ft_exit(char **args)
{
	int	status;

	rl_clear_history();
	if (!args[1])
		exit(0);
	if (!is_numeric(args[1]))
	{
		ft_printf("exit\n");
		ft_printf("exit: %s: numeric argument required\n", args[1]);
		exit(2);
	}
	if (args[2])
	{
		ft_printf("exit: too many arguments\n");
		return (1);
	}
	status = ft_atoi(args[1]);
	exit (status % 256);
}
