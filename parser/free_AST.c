#include "parser.h"

void	free_io_redir(t_io_redir *io_redir)
{
	t_io_redir	*tmp_io_redir;

	if (io_redir)
	{
		tmp_io_redir = io_redir->next;
		free(io_redir);
		free_io_redir(tmp_io_redir);
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp_cmd;

	while (cmd)
	{
		free_io_redir(cmd->cmd_prefix);
		free_io_redir(cmd->cmd_suffix);
		free_darray(cmd->cmd);
		tmp_cmd = cmd->next;
		free(cmd);
		cmd = tmp_cmd;
	}
}

void	free_AST(t_cmd_pipe *sequence)
{
	if (!sequence)
		return ;
	free_cmd(sequence->cmd);
	if (sequence->next)
		free_AST(sequence->next);
	free(sequence);
}