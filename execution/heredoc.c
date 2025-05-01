#include "execution.h"

int	here_doc(char *delimiter, t_exec *exec)
{
	char	*next_line;
	char	*expanded_line;
	int		hdfd;

	hdfd = open(".heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		ft_printf("herdoc %s> ", ((char **) exec->cmd->cmd->darray)[0]);
		next_line = get_next_line(0);
		expanded_line = expand_str(next_line, exec->env);
		free(next_line);
		if (ft_strncmp(expanded_line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(expanded_line);
			break ;
		}
		write(hdfd, expanded_line, ft_strlen(expanded_line));
		free(expanded_line);
	}
	exec->cmd->fds[0] = hdfd;
	close(exec->cmd->fds[0]);
	exec->cmd->fds[0] = open(".heredoc", O_RDONLY);
	return (0);
}