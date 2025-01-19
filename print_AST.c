#include "parser.h"

void	print_io_redir(t_io_redir *io_redir)
{
	if (io_redir)
	{
		if (io_redir->op && io_redir->op->type != END)
			ft_printf("(%s ", io_redir->op->text);
		if (io_redir->filename && io_redir->filename->type != END)
			ft_printf("%s) ", io_redir->filename->text);
		print_io_redir(io_redir->next);
	}
}

void	print_cmd(t_cmd *cmd)
{
	char	**command_list;
	command	*cmd_array;
	t_cmd	*tmp_cmd;
	t_cmd	first_command;
	size_t	i;

	tmp_cmd = cmd;
	while (cmd)
	{
		print_io_redir(cmd->cmd_prefix);
		print_io_redir(cmd->cmd_suffix);
		cmd = cmd->next;
	}
	while (tmp_cmd)
	{
		i = 0;
		cmd_array = tmp_cmd->cmd;	
		command_list = (char **) cmd_array->darray;
		while (command_list[i])
		{
			ft_printf("%s ", command_list[i]);
			i++;
		}
		tmp_cmd = tmp_cmd->next;
	}
}

void	print_AST(t_cmd_pipe *sequence)
{
	print_cmd(sequence->cmd);
	if (sequence->pipe_seq)
	{
		ft_printf("| \n");
		print_AST(sequence->pipe_seq);
	}
}