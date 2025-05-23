/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 00:55:29 by alvmoral          #+#    #+#             */
/*   Updated: 2025/05/23 13:08:09 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	free_execve(char **envp, t_exec *exec)
{
	ft_free_array(envp);
	free_ast(exec->mini->sequence);
	dict_delete(exec->mini->env);
	free(exec->mini->pids);
}

void	check_errno(int err, char **execve_args)
{
	if (err == EISDIR)
	{
		ft_putstr_fd(": Is a directory\n", 2);
		(ft_free_array(execve_args), exit(126));
	}
	else if (err == EACCES || !access(execve_args[0], X_OK))
	{
		if (!ft_strchr(execve_args[0], '/'))
		{
			ft_putstr_fd(": command not found\n", 2);
			(ft_free_array(execve_args), exit(127));
		}
		ft_putstr_fd(": Permission denied\n", 2);
		(ft_free_array(execve_args), exit(126));
	}
	else if (err == ENOENT)
	{
		ft_putstr_fd(": command not found\n", 2);
		(ft_free_array(execve_args), exit(127));
	}
	else
	{
		(ft_putstr_fd(": ", 2), ft_putstr_fd(strerror(err), 2));
		(ft_putstr_fd("\n", 2), ft_free_array(execve_args), exit(1));
	}
}

void	set_cmd_name(char **cmd_name, char ***arguments, t_exec *exec)
{
	char	**path;

	ft_bzero(cmd_name, 1024);
	ft_memcpy(cmd_name, *arguments[0], ft_strlen(*arguments[0]));
	path = ft_split(dict_get(exec->env, "PATH"), ':');
	*arguments[0] = find_exec_in_path(path, *arguments[0]);
	ft_free_array(path);
}

static void	no_such_file(char **arguments, t_exec *exec)
{
	if (arguments[0][0] == '/')
	{
		if (access(arguments[0], F_OK) != 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(arguments[0], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			(free_execution(exec), exit(127));
		}
	}
}

int	call_execve(t_exec *exec)
{
	char	**arguments;
	char	cmd_name[1024];
	char	**execve_args;
	char	**envp;

	arguments = (char **)exec->cmd->cmd->darray;
	if (arguments[0] == NULL)
		(free_execution(exec), exit(0));
	no_such_file(arguments, exec);
	set_cmd_name((char **)cmd_name, &arguments, exec);
	execve_args = create_args(exec->cmd);
	envp = dict_envp(exec->env);
	close(exec->mini->saved_std[0]);
	close(exec->mini->saved_std[1]);
	close_cmd_fds(exec->cmd);
	execve(execve_args[0], execve_args, envp);
	free_execve(envp, exec);
	(ft_putstr_fd("minishell: ", 2), ft_putstr_fd(cmd_name, 2));
	check_errno(errno, execve_args);
	return (0);
}
