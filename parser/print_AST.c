#include "parser.h"

void	print_io_redir(t_io_redir *io_redir)
{
	if (io_redir)
	{
		if (io_redir->op && io_redir->op->type != END)
			//ft_printf("\033[34m(%s ", io_redir->op->text);
			ft_printf("(%s ", io_redir->op->text);
		if (io_redir->filename && io_redir->filename->type != END)
			//ft_printf("%s)\033[0m ", io_redir->filename->text);
			ft_printf("%s) ", io_redir->filename->text);
		print_io_redir(io_redir->next);
	}
}

void	print_cmd(t_cmd *cmd)
{
	char	**command_list;
	command	*cmd_array;
	t_cmd	*tmp_cmd;
	size_t	i = 0;

	tmp_cmd = cmd;
	while (cmd)
	{
		print_io_redir(cmd->cmd_prefix);
		print_io_redir(cmd->cmd_suffix);
		cmd = cmd->next;
	}
	command_list = (char **) tmp_cmd->cmd->darray;

	//ft_printf("\033[33m{ ");
	ft_printf("{ ");
	while (command_list && command_list[i])
	{
		ft_printf("%s ", command_list[i]);
		i++;
	}
	ft_printf("} ");
}

void	print_AST(t_cmd_pipe *sequence)
{
	print_cmd(sequence->cmd);
	if (sequence->next)
	{
		ft_printf("| \n");
		print_AST(sequence->next);
	}
}