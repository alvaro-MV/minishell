#include "parser.h"

volatile sig_atomic_t	sig_int_hd = 0;

void	handle_sigint2(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	handle_sigquit2(int sig)
{
	(void)sig;
}

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	close(0);
	sig_int_hd = 1;
}

void	child_heredoc(char *delimiter, t_dictionary *env)
{
	char	*next_line;
	char	*expanded_line;
	int		hdfd;

	signal(SIGINT, handle_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
	hdfd = open(".heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (hdfd == -1)
		exit(1);
	while (1)
	{
		next_line = readline("herdoc> ");
		if (sig_int_hd == 1)
			exit(130);
		if (!next_line)
			exit(0);
		if (ft_strcmp(next_line, delimiter) == 0)
		{
			free(next_line);
			break ;
		}
		expanded_line = expand_str(next_line, env);
		write(hdfd, expanded_line, ft_strlen(expanded_line));
		write(hdfd, "\n", 1);
		free(next_line);
		free(expanded_line);
	}
	close(hdfd);
	exit(0);
}

int	here_doc(char *delimiter, t_io_redir *redir, t_dictionary **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		child_heredoc(delimiter, *env);
	signal(SIGINT, SIG_IGN);
	wait(&status);
	signal(SIGINT, handle_sigint2);
	signal(SIGQUIT, SIG_IGN);
	if (WIFSIGNALED(status) || WEXITSTATUS(status) != 0)
	{
		dict_insert(env, dict_create_entry(ft_strdup("?"),
				ft_itoa(WEXITSTATUS(status))));
		redir->fd = open(".heredoc", O_RDONLY | O_TRUNC);
		return (0);
	}
	redir->fd = open(".heredoc", O_RDONLY);
	return (1);
}
