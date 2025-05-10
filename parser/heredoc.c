#include "parser.h"

void handle_sigint2(int sig)
{
    (void)sig; // Ignorar la variable 'sig'

    
    write(1, "\n", 1); // Imprimir una nueva línea
    rl_on_new_line(); // Preparar readline para mostrar el prompt en una nueva línea
    rl_replace_line("", 0); // Limpiar la línea actual
}

// Manejador para SIGQUIT (Ctrl+\)
void handle_sigquit2(int sig)
{
    (void)sig; // Ignorar SIGQUIT, no hacemos nada
}

void handle_sigint_heredoc(int sig)
{
	(void)sig;
    rl_on_new_line(); // Preparar readline para mostrar el prompt en una nueva línea
    rl_replace_line("", 0); // Limpiar la línea actual
	close(0);
	// exit(1); // El hijo sale con error al pulsar Ctrl+C
}

void child_heredoc(char *delimiter, void *env)
{
	char *next_line;
	char *expanded_line;
	int hdfd;

	signal(SIGINT, handle_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);

	hdfd = open(".heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (hdfd == -1)
		exit(1);

	while (1)
	{
		next_line = readline("herdoc> ");
		if (!next_line)
			exit(0); // EOF o stdin cerrado

		if (strcmp(next_line, delimiter) == 0)
		{
			free(next_line);
			break;
		}
		expanded_line = expand_str(next_line, env);
		write(hdfd, expanded_line, strlen(expanded_line));
		write(hdfd, "\n", 1);
		free(next_line);
		free(expanded_line);
	}
	close(hdfd);
	exit(0);
}

void here_doc(char *delimiter, t_io_redir *redir, t_dictionary *env)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
		child_heredoc(delimiter, env);

	signal(SIGINT, SIG_IGN); // Ignorar Ctrl+C en el padre mientras espera

	// waitpid(pid, &status, 0);
	wait(&status);

	signal(SIGINT, handle_sigint2); // Restaurar señales
	signal(SIGQUIT, SIG_IGN);

	if (WIFSIGNALED(status) || WEXITSTATUS(status) != 0)
	{
		write(1, "Holaaaa\n", 9);
		unlink(".heredoc");
		return;
	}
	ft_printf("status: %d\n", status);
	redir->fd = open(".heredoc", O_RDONLY);
}