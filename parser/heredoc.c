#include "parser.h"

// void handle_sigint_heredoc(int sig)
// {
// 	(void) sig;
// 	//exit (0);
// }

// void signals_heredoc(char **input, int *exit)
// {
//     // char *input;

//     // Configurar manejadores de señales
//     signal(SIGINT, handle_sigint_heredoc);  // Capturar Ctrl+C
//     signal(SIGQUIT, handle_sigquit);

//     // Bucle principal para el shell interactivo
//     // while (1)
// 	ft_printf("herdoc> ");
// 	*input = get_next_line(0);
// 	// *input = readline("herdoc> "); // Mostrar prompt y leer entrada
// 	if (!*input)
// 	{
// 		*exit = 1;
// 	}
// }

void	here_doc(char *delimiter, t_io_redir *redir, t_dictionary *env)
{
	char	*next_line;
	char	*expanded_line;
	int		hdfd;
	
	hdfd = open(".heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		// ft_printf("herdoc %s> ", ((char **) exec->cmd->cmd->darray)[0]);
		// signals_heredoc(&next_line, &finish);
		next_line = readline("heredoc> ");
		if (!next_line)
		{
			redir->fd = open(".heredoc", O_RDONLY | O_TRUNC);
			// free(next_line);
			return ;
		}
		// {
		// 	open(".heredoc", O_RDONLY | O_TRUNC);
			// return (0);
		// }
		if (*next_line == '\0')
		{
			break ;
		}
		expanded_line = expand_str(next_line, env);
		free(next_line);
		if (ft_strncmp(expanded_line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(expanded_line);
			break ;
		}
		write(hdfd, expanded_line, ft_strlen(expanded_line));
		write(hdfd, "\n", 1);
		free(expanded_line);
	}
	redir->fd = open(".heredoc", O_RDONLY);
}