/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_io_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:19:21 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/22 23:15:29 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	override_fd(t_exec *exec, t_io_redir *redir, int flags, int idx)
{
	int			fd;
	struct stat	file_stat;

	fd = open(redir->filename->text, flags, 0644);
	if (fd == -1)
	{
		perror(redir->filename->text);
		if (access(redir->filename->text, F_OK))
			return (1);
		if (stat(redir->filename->text, &file_stat) == -1)
			return (1);
		if (!(file_stat.st_mode & S_IWUSR) || !(file_stat.st_mode & S_IRUSR))
			return (1);
		else
			return (1);
	}
	else
	{
		if (exec->cmd->fds[idx] > 2)
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

int	check_redir_status(t_exec *exec, t_io_redir *ix, t_cmd *tmp_cmd)
{
	int			status;

	status = traverse_io_redir(ix, exec);
	if (status != 0)
	{
		exec->cmd = tmp_cmd;
		return (status);
	}
	return (0);
}

int	exec_prefix_suffix(t_cmd *tmp_cmd, t_exec *exec, t_cmd *cmd)
{
	t_io_redir	*prefix;
	t_io_redir	*suffix;
	int			status;

	prefix = cmd->cmd_prefix;
	suffix = cmd->cmd_suffix;
	while (prefix)
	{
		status = check_redir_status(exec, prefix, tmp_cmd);
		if (status)
			return (status);
		prefix = prefix->next;
	}
	while (suffix)
	{
		status = check_redir_status(exec, suffix, tmp_cmd);
		if (status)
			return (status);
		suffix = suffix->next;
	}
	return (0);
}

int	execute_io_redir(t_exec *exec)
{
	t_cmd		*cmd;
	t_cmd		*tmp_cmd;
	int			status;

	tmp_cmd = exec->cmd;
	cmd = exec->cmd;
	while (cmd)
	{
		status = exec_prefix_suffix(tmp_cmd, exec, cmd);
		if (status)
			return (status);
		cmd = cmd->next;
	}
	exec->cmd = tmp_cmd;
	return (status);
}
