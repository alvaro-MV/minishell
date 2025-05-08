#include "execution.h"

void handle_sigint_heredoc(int sig)
{
	(void) sig;
	//exit (0);
}

void signals_heredoc(char **input, int *exit)
{
    // char *input;

    // Configurar manejadores de señales
    signal(SIGINT, handle_sigint_heredoc);  // Capturar Ctrl+C
    signal(SIGQUIT, handle_sigquit);

    // Bucle principal para el shell interactivo
    // while (1)
	ft_printf("herdoc> ");
	*input = get_next_line(0);
	// *input = readline("herdoc> "); // Mostrar prompt y leer entrada
	if (!*input)
	{
		*exit = 1;
	}
}

int	here_doc(char *delimiter, t_exec *exec)
{
	char	*next_line;
	char	*expanded_line;
	int		finish;
	int		hdfd;
	int		pruebaaa = 0; // testeo

	finish = 0;
	hdfd = open(".heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		// ft_printf("herdoc %s> ", ((char **) exec->cmd->cmd->darray)[0]);
		ft_printf(" %d", pruebaaa);
		signals_heredoc(&next_line, &finish);
		if (finish)
		{
			exec->cmd->fds[0] = hdfd;
			close(exec->cmd->fds[0]);
			exec->cmd->fds[0] = open(".heredoc", O_RDONLY | O_TRUNC);
			free(next_line);
			return (0);
		}
		// {
		// 	open(".heredoc", O_RDONLY | O_TRUNC);
			// return (0);
		// }
		if (*next_line == '\0')
		{
			break ;
		}
		expanded_line = expand_str(next_line, exec->env);
		free(next_line);
		if (ft_strncmp(expanded_line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(expanded_line);
			break ;
		}
		write(hdfd, expanded_line, ft_strlen(expanded_line));
		write(hdfd, "\n", 1);
		free(expanded_line);
		pruebaaa++;
	}
	exec->cmd->fds[0] = hdfd;
	close(exec->cmd->fds[0]);
	exec->cmd->fds[0] = open(".heredoc", O_RDONLY);
	return (0);
}