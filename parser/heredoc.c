/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:47:46 by alvmoral          #+#    #+#             */
/*   Updated: 2025/05/17 19:27:33y alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*get_hd_name(void)
{
	char	*hd_name;
	char	*tmp;
	int		count_hd;

	count_hd = 0;
	tmp = NULL;
	hd_name = ft_strdup("./.heredoc");
	while (!access(hd_name, F_OK))
	{
		tmp = ft_itoa(count_hd);
		free(hd_name);
		hd_name = ft_strjoin("./.heredoc_", tmp);
		free(tmp);
		count_hd++;
	}
	return (hd_name);
}

void	process_heredoc_loop(int hdfd, char *delimiter, t_dictionary *env)
{
	char	*next_line;
	char	*expanded_line;

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
	exit(0);
}

void	child_heredoc(t_io_redir *redir, char *delimiter, void *env)
{
	int	hdfd;

	signal(SIGINT, handle_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
	hdfd = open(redir->hd_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (hdfd == -1)
		exit(1);
	process_heredoc_loop(hdfd, delimiter, env);
	close(hdfd);
	exit(0);
}

int	here_doc(char *delimiter, t_io_redir *redir, t_dictionary *env)
{
	pid_t	pid;
	int		status;

	redir->hd_name = get_hd_name();
	pid = fork();
	if (pid == 0)
		child_heredoc(redir, delimiter, env);
	signal(SIGINT, SIG_IGN);
	wait(&status);
	signal(SIGINT, handle_sigint2);
	signal(SIGQUIT, SIG_IGN);
	if (WIFSIGNALED(status) || WEXITSTATUS(status) != 0)
	{
		storage_signal(WEXITSTATUS(status), 1);
		return (WEXITSTATUS(status));
	}
	return (0);
}