#include "execution.h"

int	here_doc(char *delimiter, t_dictionary *env)
{
	char	*next_line;
	char	*expanded_line;
	int		infd[2];

	pipe(infd);
	if (delimiter[ft_strlen(delimiter)-1] != '\n')
	{
		delimiter = ft_strjoin(delimiter, "\n");
		if (delimiter == NULL)
			return (-1);
	}
<<<<<<< HEAD
	close(exec->cmd->fds[0]);
<<<<<<< HEAD
	dup2(exec->saved_stdin, STDIN_FILENO);
	close(exec->saved_stdin);
=======
>>>>>>> parent of 4827366 (Errors in heredoc, where multiple redirections o pipe exist.)
=======
>>>>>>> parent of 4b36d40 (heredoc working fine. with ls | cat << l)
	while (1)
	{
		ft_printf("herdoc> ");
		next_line = get_next_line(0);
		expanded_line = expand_str(next_line, env);
		if (ft_strcmp(expanded_line, delimiter) == 0)
		{
			free(expanded_line);
			break ;
		}
		write(infd[1], expanded_line, ft_strlen(expanded_line));
		free(expanded_line);
	}
	free(delimiter);
	close(infd[1]);
	dup2(infd[0], 0);
	close(infd[0]);
	return (0);
}

//por que no esta funcionando???