#include "execution.h"
#include <sys/types.h>
#include <sys/stat.h>

int	override_fd(t_exec *exec, t_io_redir *redir, int flags, int idx)
{
	int	fd;
	struct stat file_stat;

	fd = open(redir->filename->text, flags, 0644);
	if (fd == -1)
	{
		if (access(redir->filename->text, F_OK))
		{
			perror(redir->filename->text);
			return (1);
		}
		if (stat(redir->filename->text, &file_stat) == -1)
		{
			perror(redir->filename->text);
			return (1); // Devolver código de error si stat falla
		}
		if (!(file_stat.st_mode & S_IWUSR) || !(file_stat.st_mode & S_IRUSR))
		{
			perror(redir->filename->text);
			free_cmd(exec->cmd);
			dict_delete(exec->env);
			exit (1);
		}
	}
	else
	{
		// close(exec->cmd->fds[idx]);
		// if (dup2(fd, idx) == -1)
		// 	return (1); // Me joden
		exec->cmd->fds[idx] = fd;
		// close(fd);
	}
	return (0);
}

int	traverse_io_redir(t_io_redir *ix, t_exec *exec)
{
	int status;

	status = 0;
	if (ix->op && ix->op->type != END && !ft_strncmp(ix->op->text, "<", 2))
		status = override_fd(exec, ix, O_RDONLY, 0);
	else if (ix->op && ix->op->type != END && !ft_strncmp(ix->op->text, "<<", 2))
	{
		exec->cmd->fds[0] = ix->fd;
		status = 0;
	}
	else if (ix->op && ix->op->type != END && !ft_strncmp(ix->op->text, ">", 2))
		status = override_fd(exec, ix, O_RDWR | O_CREAT | O_TRUNC, 1);
	else if (ix->op && ix->op->type != END && !ft_strncmp(ix->op->text, ">>", 2))
		status = override_fd(exec, ix, O_RDWR | O_APPEND | O_CREAT, 1);
	return (status);
}

int		execute_io_redir(t_exec *exec)
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
