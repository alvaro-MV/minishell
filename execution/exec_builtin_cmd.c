/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:19:07 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/23 14:50:28 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*find_exec_in_path(char **path, char *exec)
{
	int		l_exec;
	int		l_path;
	char	pathname[1024];

	// if (access(exec, X_OK) == 0)
	// 	return (ft_strdup(exec));
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

void	free_execution(t_exec *exec_vars)
{
	close_cmd_fds(exec_vars->cmd);
	free_ast(exec_vars->mini->sequence);
	dict_delete(exec_vars->mini->env);
	free(exec_vars->mini->pids);
	close(exec_vars->mini->saved_std[0]);
	close(exec_vars->mini->saved_std[1]);
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
	{
		rl_clear_history();
		status = ft_exit(exec, arguments);
	}
	else if (!ft_strcmp(arguments[0], "unset"))
		unset(exec, arguments);
	else if (!ft_strcmp(arguments[0], "cd"))
		status = cd(exec, arguments);
	else
		ft_printf("minishell: command not found\n");
	return (ft_free_array(arguments), status);
}

int	handle_child_process(t_exec *exec_vars)
{
	int	status;

	status = execute_io_redir(exec_vars);
	if (status)
	{
		free_execution(exec_vars);
		exit(1);
	}
	if (exec_vars->cmd->fds[0] != 0 && dup2(exec_vars->cmd->fds[0], 0) == -1)
		write(1, "Failed to redirect stdin.\n", 26);
	if (exec_vars->cmd->fds[1] != 1 && dup2(exec_vars->cmd->fds[1], 1) == -1)
		write(1, "Failed to redirect stdout.\n", 27);
	close_cmd_fds(exec_vars->cmd);
	if (status != 0)
		(free_execution(exec_vars), exit(status));
	if (!status && is_builtin(exec_vars->cmd->cmd->darray))
	{
		status = run_builtin(exec_vars);
		free_execution(exec_vars);
		exit(status);
	}
	else if (!status && !is_builtin(exec_vars->cmd->cmd->darray))
		status = call_execve(exec_vars);
	free_execution(exec_vars);
	exit(status);
}

int	execute_child(t_exec *exec_vars, t_cmd_pipe *sequence)
{
	int			ret;
	t_cmd_pipe	*tmp;

	ret = fork();
	if (ret == 0)
	{
		rl_clear_history();
		while (sequence)
		{
			tmp = sequence->next;
			if (sequence->cmd != exec_vars->cmd)
			{
				close_cmd_fds(sequence->cmd);
			}
			sequence = tmp;
		}
		handle_child_process(exec_vars);
	}
	else
		close_cmd_fds(exec_vars->cmd);
	return (ret);
}
