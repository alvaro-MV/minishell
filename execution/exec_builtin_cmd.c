#include "execution.h"

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

int	call_execve(t_exec exec)
{
	int		status;
	char	**arguments;

	arguments = (char **)exec.cmd->cmd->darray;
	arguments[0] = find_exec_in_path(ft_split(dict_get(exec.env, "PATH"), ':'), arguments[0]);
	execve(((char **)exec.cmd->cmd->darray)[0], arguments, NULL);
	ft_putstr_fd(arguments[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	ft_free_array(arguments);
	exit(127);
}

int	run_builtin(t_exec exec)
{
	char	**arguments;
	int		i;

	i = 0;
	arguments = (char **)exec.cmd->cmd->darray;
	while (arguments[i])
	{
		arguments[i] = expand_str(arguments[i], exec.env);
		i++;
	}
	if (!ft_strncmp(arguments[0], "echo", ft_strlen("echo")))
		echo(arguments);
	// else if (!ft_strncmp(arguments[0], "export", ft_strlen("export")))
	// 	export(arguments);
}

int	execute_child(t_exec exec_vars)
{
	int	ret;
	int	status;

	ret = fork();
	status = 0;
	// if (ret == -1)
	// 	//Pirarte
	if (ret == 0)
	{
		if (exec_vars.cmd->fds[0] != 0 && dup2(exec_vars.cmd->fds[0], 0) == -1)
			write(1, "Nooooooooo\n", 12); // Liberar lo anterior y pirarte.
		if (exec_vars.cmd->fds[1] != 1 && dup2(exec_vars.cmd->fds[1], 1) == -1)
			write(1, "Nooooooooo\n", 12); // Liberar lo anterior y pirarte.
		execute_io_redir(exec_vars); // Basicamente, intercambian un fd por otro.
		
		if (is_builtin(exec_vars.cmd->cmd->darray))
			status = run_builtin(exec_vars);
		else
			status = call_execve(exec_vars); // funcion para determinar si se ejecuta con execve o es un built-in.
		close_cmd_fds(exec_vars.cmd);
	}
	else
		close_cmd_fds(exec_vars.cmd);
	return (status);
}
