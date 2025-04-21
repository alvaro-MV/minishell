#include "execution.h"

int	is_builtin(char **cmd_args)
{
	char	*cmd_name;

	cmd_name = cmd_args[0];
	if (!cmd_name)
		return (0);
	if (!ft_strcmp(cmd_name, "echo"))
		return (1);
	else if (!ft_strcmp(cmd_name, "export"))
		return (1);
	else if (!ft_strcmp(cmd_name, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd_name, "env"))
		return (1);
	//Meter el resto
	return (0);
}

void	close_cmd_fds(t_cmd *cmd)
{
	if (cmd->fds[0] > 2)
		close(cmd->fds[0]);
	if (cmd->fds[1] > 2)
		close(cmd->fds[1]);
}