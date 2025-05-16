/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:19:07 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/16 13:00:41 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <errno.h>

char	*find_exec_in_path(char **path, char *exec)
{
	int		l_exec;
	int		l_path;
	char	pathname[1024];

	if (access(exec, X_OK) == 0)
		return (ft_strdup(exec));
	if (exec[0] == '/')
		return (NULL);
	l_exec = ft_strlen(exec);
	l_path = 0;
	if (path != NULL)
	{
		while (*path != NULL)
		{
			l_path = ft_strlen(*path);
			ft_strlcpy(pathname, *path, l_path + 2);
			if (pathname[l_path - 1] != '/')
				ft_strlcat(pathname, "/", l_path + 2);
			ft_strlcat(pathname, exec, l_exec + l_path + 2);
			if (access(pathname, X_OK) == 0)
				return (free(exec), ft_strdup(pathname));
			path++;
		}
	}
	return (exec);
}

int	call_execve(t_exec *exec)
{
	char	**arguments;
	char	cmd_name[1024];
	char	**execve_args;
	char	**envp;
	char	**path;

	arguments = (char **)exec->cmd->cmd->darray;
	ft_bzero(cmd_name, 1024);
	ft_memcpy(cmd_name, arguments[0], ft_strlen(arguments[0]));
	path = ft_split(dict_get(exec->env, "PATH"), ':');
	arguments[0] = find_exec_in_path(path, arguments[0]);
	ft_free_array(path);
	execve_args = create_args(exec->cmd);
	envp = dict_envp(exec->env, 0, 0);
	
	execve(execve_args[0], execve_args, envp);
	ft_free_array(envp);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_name, 2);
	if (access(execve_args[0], F_OK) == 0)
		(ft_putstr_fd(": Permission denied\n", 2), exit(126));
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

int	run_builtin(t_exec *exec)
{
	char	**arguments;
	int		status;

	status = 0;
	arguments = create_args(exec->cmd);
	if (!ft_strcmp(arguments[0], "echo"))
		echo(arguments);
	else if (!ft_strcmp(arguments[0], "export"))
		status = export(exec, arguments);
	else if (!ft_strcmp(arguments[0], "pwd"))
		pwd2();
	else if (!ft_strcmp(arguments[0], "env"))
		ft_env(arguments, exec);
	else if (!ft_strcmp(arguments[0], "exit"))
		status = ft_exit(arguments);
	else if (!ft_strcmp(arguments[0], "unset"))
		unset(exec, arguments);
	else if (!ft_strcmp(arguments[0], "cd"))
		status = cd(exec, arguments);
	else
		ft_printf("minishell: command not found\n");
	free(arguments);
	return (status);
}

int	handle_child_process(t_exec *exec_vars)
{
	int	status;

	status = execute_io_redir(exec_vars);
	if (status)
		exit(1);
	if (exec_vars->cmd->fds[0] != 0 && dup2(exec_vars->cmd->fds[0], 0) == -1)
		write(1, "Failed to redirect stdin.\n", 26);
	if (exec_vars->cmd->fds[1] != 1 && dup2(exec_vars->cmd->fds[1], 1) == -1)
		write(1, "Failed to redirect stdout.\n", 27);
	if (status != 0)
	{
		close_cmd_fds(exec_vars->cmd);
		exit(status);
	}
	if (!status && is_builtin(exec_vars->cmd->cmd->darray))
		exit(run_builtin(exec_vars));
	else if (!status && !is_builtin(exec_vars->cmd->cmd->darray))
		status = call_execve(exec_vars);
	close_cmd_fds(exec_vars->cmd);
	return (status);
}

int	execute_child(t_exec *exec_vars)
{
	int	ret;
	int	status;

	status = 0;
	ret = fork();
	if (ret == 0)
	{
		ret = fork();
		status = handle_child_process(exec_vars);
	}
	else
		close_cmd_fds(exec_vars->cmd);
	return (ret);
}
