/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:47:46 by alvmoral          #+#    #+#             */
/*   Updated: 2025/05/16 16:51:02 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


void	handle_sigint2(int sig)
{
	storage_signal(128 + sig, 1);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	handle_sigquit2(int sig)
{
	storage_signal(128 + sig, 1);
}

void	handle_sigint_heredoc(int sig)
{
	storage_signal(128 + sig, 1);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	close(0);
}

void	child_heredoc(char *delimiter, void *env)
{
	char	*next_line;
	char	*expanded_line;
	int		hdfd;

	(signal(SIGINT, handle_sigint_heredoc), signal(SIGQUIT, SIG_IGN));
	hdfd = open(".heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (hdfd == -1)
		exit(1);
	while (1)
	{
		next_line = readline("herdoc> ");
		if (storage_signal(0, 0))
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
		(write(hdfd, "\n", 1), free(next_line), free(expanded_line));
	}
	(close(hdfd), exit(0));
}

int	here_doc(char *delimiter, t_io_redir *redir, t_dictionary *env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		child_heredoc(delimiter, env);
	signal(SIGINT, SIG_IGN);
	wait(&status);
	signal(SIGINT, handle_sigint2);
	signal(SIGQUIT, SIG_IGN);
	if (WIFSIGNALED(status) || WEXITSTATUS(status) != 0)
	{
		storage_signal(WEXITSTATUS(status), 1);
		// dict_insert(&env, dict_create_entry(ft_strdup("?"), ft_itoa(WEXITSTATUS(status))));
		redir->fd = open(".heredoc", O_RDONLY | O_TRUNC);
		return (WEXITSTATUS(status));
	}
	redir->fd = open(".heredoc", O_RDONLY);
	return (0);
}
