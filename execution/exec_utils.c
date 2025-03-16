#include "execution.h"

int	is_builtin(char **cmd_args)
{
	char	*cmd_name;

	cmd_name = cmd_args[0];
	if (!ft_strncmp(cmd_name, "echo", ft_strlen("echo")))
		return (1);
	else if (!ft_strncmp(cmd_name, "export", ft_strlen("export")))
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