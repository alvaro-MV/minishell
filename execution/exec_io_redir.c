/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_io_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:19:21 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/18 17:06:50by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	override_fd(t_exec *exec, t_io_redir *redir, int flags, int idx)
{
	int			fd;
	struct stat	file_stat;

	ft_printf("filename: %s\n", redir->filename->text);
	fd = open(redir->filename->text, flags, 0644);
	if (fd == -1)
	{
		perror(redir->filename->text);
		if (access(redir->filename->text, F_OK))
			return (1);
		if (stat(redir->filename->text, &file_stat) == -1)
			return (1);
		if (!(file_stat.st_mode & S_IWUSR) || !(file_stat.st_mode & S_IRUSR))
		{
			free_cmd(exec->cmd, 0);
			dict_delete(exec->env);
			return (1);
		}
		else
			return (1);
	}
	else
	{
		close(exec->cmd->fds[idx]);
		exec->cmd->fds[idx] = fd;
	}
	return (0);
}

int	traverse_io_redir(t_io_redir *ix, t_exec *exec)
{
	int	status;

	status = 0;
	if (ix->op && ix->op->type != END && !ft_strncmp(ix->op->text, "<", 2))
	{
		status = override_fd(exec, ix, O_RDONLY, 0);
	}
	else if (ix->op && ix->op->type != END && !ft_strncmp(ix->op->text, "<<",
			2))
	{
		exec->cmd->fds[0] = open(ix->hd_name, O_RDONLY);
		if (exec->cmd->fds[0] == -1)
			return (1);
	}
	else if (ix->op && ix->op->type != END && !ft_strncmp(ix->op->text, ">", 2))
	{
		status = override_fd(exec, ix, O_WRONLY | O_CREAT | O_TRUNC, 1);
	}
	else if (ix->op && ix->op->type != END && !ft_strncmp(ix->op->text, ">>",
			2))
	{
		status = override_fd(exec, ix, O_WRONLY | O_CREAT | O_APPEND, 1);
	}
	return (status);
}

int	execute_io_redir(t_exec *exec)
{
	t_io_redir	*prefix;
	t_io_redir	*suffix;
	int			status;

	prefix = exec->cmd->cmd_prefix;
	suffix = exec->cmd->cmd_suffix;
	status = 0;
	while (prefix)
	{
		status = traverse_io_redir(prefix, exec);
		if (status != 0)
			return (status);
		prefix = prefix->next;
	}
	while (suffix)
	{
		status = traverse_io_redir(suffix, exec);
		if (status != 0)
			return (status);
		suffix = suffix->next;
	}
	return (status);
}
