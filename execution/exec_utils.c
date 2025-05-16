/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:20:14 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/16 13:00:59 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	**create_args(t_cmd *cmd)
{
	char	**command_list;
	t_command	*ret_array;
	char	**tmp_array;
	size_t	i;

	ret_array = alloc_darray(10, sizeof(char *));
	if (!ret_array)
		return (NULL);
	while (cmd)
	{
		i = 0;
		command_list = (char **)cmd->cmd->darray;
		while (command_list && command_list[i])
		{
			if (!append_darray(&ret_array, &command_list[i]))
				return (NULL);
			i++;
		}
		cmd = cmd->next;
	}
	tmp_array = (char **)ret_array->darray;
	free(ret_array);
	return (tmp_array);
}

int	is_builtin(char **cmd_args)
{
	char	*cmd_name;

	cmd_name = cmd_args[0];
	if (!cmd_name)
		return (0);
	if (!ft_strcmp(cmd_name, "echo"))
		return (1);
	else if (!ft_strcmp(cmd_name, "export"))
		return (1);
	else if (!ft_strcmp(cmd_name, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd_name, "env"))
		return (1);
	else if (!ft_strcmp(cmd_name, "unset"))
		return (1);
	else if (!ft_strcmp(cmd_name, "exit"))
		return (1);
	else if (!ft_strcmp(cmd_name, "cd"))
		return (1);
	return (0);
}

void	close_cmd_fds(t_cmd *cmd)
{
	if (cmd->fds[0] > 2)
		close(cmd->fds[0]);
	if (cmd->fds[1] > 2)
		close(cmd->fds[1]);
}
