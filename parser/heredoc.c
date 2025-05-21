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

// #include "parser.h"

// char	*get_hd_name(void)
// {
// 	char	*hd_name;
// 	char	*tmp;
// 	int		count_hd;

// 	count_hd = 0;
// 	tmp = NULL;
// 	hd_name = ft_strdup("./.heredoc");
// 	while (!access(hd_name, F_OK))
// 	{
// 		tmp = ft_itoa(count_hd);
// 		free(hd_name);
// 		hd_name = ft_strjoin("./.heredoc_", tmp);
// 		free(tmp);
// 		count_hd++;
// 	}
// 	return (hd_name);
// }

// void	process_heredoc_loop(int hdfd, char *delimiter, t_dictionary *env)
// {
// 	char	*next_line;
// 	char	*expanded_line;

// 	while (1)
// 	{
// 		next_line = readline("herdoc> ");
// 		if (storage_signal(0, 0))
// 			exit(130);
// 		if (!next_line)
// 			exit(0);
// 		if (ft_strcmp(next_line, delimiter) == 0)
// 		{
// 			free(next_line);
// 			break ;
// 		}
// 		expanded_line = expand_str(next_line, env);
// 		write(hdfd, expanded_line, ft_strlen(expanded_line));
// 		(write(hdfd, "\n", 1), free(next_line), free(expanded_line));
// 	}
// 	exit(0);
// }

// void	child_heredoc(t_io_redir *redir, t_token **stream, 
// 		char *delimiter, void *env)
// {
// 	int	hdfd;

// 	(void) stream;
// 	signal(SIGINT, handle_sigint_heredoc);
// 	signal(SIGQUIT, SIG_IGN);
// 	hdfd = open(redir->hd_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
// 	if (hdfd == -1)
// 		exit(1);
// 	process_heredoc_loop(hdfd, delimiter, env);
// 	close(hdfd);
// 	exit(0);
// }

// int	here_doc(t_token **stream, t_io_redir *redir, t_dictionary *env)
// {
// 	pid_t	pid;
// 	int		status;

// 	redir->hd_name = get_hd_name();
// 	if (!redir->hd_name)
// 		return (1);
// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		perror("fork");
// 		free(redir->hd_name);
// 		redir->hd_name = NULL;
// 		return (1);
// 	}
// 	if (pid == 0)
// 	{
// 		child_heredoc(redir, stream, redir->filename->text, env);
// 		free(redir->hd_name);
// 		exit(EXIT_SUCCESS);
// 	}
// 	signal(SIGINT, SIG_IGN);
// 	wait(&status);
// 	signal(SIGINT, handle_sigint2);
// 	signal(SIGQUIT, SIG_IGN);
// 	if (WIFSIGNALED(status) || WEXITSTATUS(status) != 0)
// 	{
// 		storage_signal(WEXITSTATUS(status), 1);
// 		free(redir->hd_name);
// 		redir->hd_name = NULL;
// 		return (WEXITSTATUS(status));
// 	}
// 	return (0);
// }

/* ───────────────────── heredoc_utils.c ───────────────────── */
#include "parser.h"
#include "../libft/include/get_next_line.h"
#include <signal.h>
#include <fcntl.h>

char	*get_hd_name(void)
{
	char	*hd_name;
	char	*tmp;
	int		count_hd;

	count_hd = 0;
	hd_name = ft_strdup("./.heredoc");
	while (!access(hd_name, F_OK))
	{
		tmp = ft_itoa(count_hd++);
		free(hd_name);
		hd_name = ft_strjoin("./.heredoc_", tmp);
		free(tmp);
	}
	return (hd_name);
}


/* ── 2.  Bucle con gnl ─────────────────────────────────────────── */
static int	process_heredoc_loop(int hdfd,
								char *delimiter,
								t_dictionary *env)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		ft_printf("herdoc> ");                 /* prompt */
		line = get_next_line(STDIN_FILENO);
		if (storage_signal(0, 0) != 0)
			return (-1);
		if (!line)                             /* EOF → fin heredoc           */
			break ;
		if (storage_signal(0, 0))              /* ^C detectado                */
			return (free(line), -1);
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (ft_strcmp(line, delimiter) == 0)
			return (free(line), 0);            // free str in gnl
		expanded = expand_str(line, env);
		write(hdfd, expanded, ft_strlen(expanded));
		write(hdfd, "\n", 1);
		free(line);
		free(expanded);
	}
	return (0);
}

// static int	process_heredoc_loop(int hdfd, char *delimiter, t_dictionary *env)
// {
// 	char	*line;
// 	char	*expanded;

// 	ft_printf("herdoc> ");
// 	while ((line = get_next_line(STDIN_FILENO)))
// 	{
// 		ft_printf("herdoc> ");                        
// 		if (line[ft_strlen(line) - 1] == '\n')
// 			line[ft_strlen(line) - 1] = '\0';
// 		if (storage_signal(0, 0))
// 			return (free(line), -1);
// 		if (ft_strcmp(line, delimiter) == 0)
// 			return (free(line), 0);
// 		expanded = expand_str(line, env);
// 		write(hdfd, expanded, ft_strlen(expanded));
// 		write(hdfd, "\n", 1);
// 		free(line);
// 		free(expanded);
// 	}
// 	return (0);
// }

int	here_doc(t_token **stream, t_io_redir *redir, t_dictionary *env)
{
	int		hdfd;
	int		ret;

	(void)stream;
	redir->hd_name = get_hd_name();
	if (!redir->hd_name)
		return (1);
	signal(SIGINT, handle_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);

	hdfd = open(redir->hd_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (hdfd == -1)
		return (free(redir->hd_name), redir->hd_name = NULL, 1);

	ret = process_heredoc_loop(hdfd, redir->filename->text, env);
	close(hdfd);
	signal(SIGINT, handle_sigint2);
	signal(SIGQUIT, SIG_IGN);

	if (ret == -1)
	{
		unlink(redir->hd_name);
		free(redir->hd_name);
		redir->hd_name = NULL;
		storage_signal(130, 1);
		return (1);
	}
	return (0);
}
