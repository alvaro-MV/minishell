#include "execution.h"

int	override_fd(t_exec exec, t_io_redir *redir, int flags, int idx)
{
	int	fd;

	fd = open(redir->filename->text, flags, 0644);
	if (fd == -1)
	{
		perror(redir->filename->text);
		return (2);
	}
	else
	{
		close(exec.cmd->fds[idx]);
		if (dup2(fd, idx) == -1)
			; // Me joden
		exec.cmd->fds[idx] = fd;
	}
	return (1);
}

// int	override_fd_here_doc(t_exec exec, t_io_redir *ix)
// {
// 	int	fd;
// 	fd = heredoc(ix->filename); //filename es el delitimador.
// 	if (fd == -1)
// 		; //Pirarte y liberar
// 	else
// 	{
// 		close(exec.cmd->fds[0]);
// 		exec.cmd->fds[0] = fd;
// 	}
// }

void	traverse_io_redir(t_io_redir *ix, t_exec exec)
{
	if (ix->op && ix->op->type != END && !ft_strncmp(ix->op->text, "<", 2))
		override_fd(exec, ix, O_RDONLY, 0);
	else if (ix->op && ix->op->type != END && !ft_strncmp(ix->op->text, "<<", 2))
		here_doc(ix->filename->text);
	else if (ix->op && ix->op->type != END && !ft_strncmp(ix->op->text, ">", 2))
		override_fd(exec, ix, O_RDWR | O_CREAT | O_TRUNC, 1);
	else if (ix->op && ix->op->type != END && !ft_strncmp(ix->op->text, ">>", 2))
		override_fd(exec, ix, O_RDWR | O_APPEND | O_TRUNC, 1);
}

int	execute_io_redir(t_exec exec)
{
	t_io_redir	*prefix;
	t_io_redir	*suffix;

	prefix = exec.cmd->cmd_prefix;
	suffix = exec.cmd->cmd_suffix;
	while (prefix)
	{
		traverse_io_redir(prefix, exec);
		prefix = prefix->next;
	}
	while (suffix)
	{
		traverse_io_redir(suffix, exec);
		suffix = suffix->next;
	}
	return (1);
}
