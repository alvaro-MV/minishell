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
	char	**arguments;
	char	**execve_args;

	arguments = (char **)exec.cmd->cmd->darray;
	arguments[0] = find_exec_in_path(ft_split(dict_get(exec.env, "PATH"), ':'), arguments[0]);
	execve_args = create_args(exec.cmd);
	//Controlar el caso donde sea ruta relativa o absoluta que este mal.
	execve(execve_args[0], execve_args, NULL);
	ft_putstr_fd(arguments[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free_cmd(exec.cmd);
	dict_delete(exec.env);
	ft_free_array(arguments);
	exit(127);
}

int	run_builtin(t_exec exec)
{
	char	**arguments;

	arguments = create_args(exec.cmd);
	if (!ft_strcmp(arguments[0], "echo"))
		echo(arguments);
	else if (!ft_strcmp(arguments[0], "export"))
		return (export(&exec, arguments));
	else if (!ft_strcmp(arguments[0], "pwd"))
		pwd2();
	else if (!ft_strcmp(arguments[0], "env"))
		ft_env(arguments, &exec);
	else
		ft_printf("minishell: command not found\n");
	return (0);
}

int	execute_child(t_exec exec_vars)
{
	int	ret;
	int	status;

	status = 0;
	ret = fork();
	// if (ret == -1)
	// 	//Pirarte
	if (ret == 0)
	{
		if (exec_vars.cmd->fds[0] != 0 && dup2(exec_vars.cmd->fds[0], 0) == -1)
			write(1, "Siiiiiiiiiiiii\n", 12); // Liberar lo anterior y pirarte.
		if (exec_vars.cmd->fds[1] != 1 && dup2(exec_vars.cmd->fds[1], 1) == -1)
			write(1, "Siiiiiiiiiiiii\n", 12); // Liberar lo anterior y pirarte.
		status = execute_io_redir(exec_vars); // Basicamente, intercambian un fd por otro.
		if (status != 0)
		{
			// ft_printf("PERO TE PIRAS O NO TE PIRAS JODER: %d\n", status);
			close_cmd_fds(exec_vars.cmd);
			exit(status);
		}
		if (!status && is_builtin(exec_vars.cmd->cmd->darray))
			exit(run_builtin(exec_vars));
		else if (!status && !is_builtin(exec_vars.cmd->cmd->darray))
			status = call_execve(exec_vars); // funcion para determinar si se ejecuta con execve o es un built-in.
		close_cmd_fds(exec_vars.cmd);
	}
	else
		close_cmd_fds(exec_vars.cmd);
	ft_printf("status: %d\n", status);
	return (status);
}

// bool handle_redirection(t_exec exec_vars)
// {
//     if (exec_vars.cmd->fds[1] > 1) {  // Redirección de salida
//         if (access(exec_vars.cmd->, F_OK) == -1) {
//             // Si el archivo no existe, verificar permisos del directorio
//             char *dir = dirname(exec_vars.cmd->outfile);
//             if (access(dir, W_OK) != 0) {
//                 return false;
//             }
//         } else if (access(exec_vars.cmd->outfile, W_OK) != 0) {
//             return false;  // No hay permisos de escritura
//         }
//     }
//     return true;
// }