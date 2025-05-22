/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:47:46 by alvmoral          #+#    #+#             */
/*   Updated: 2025/05/22 23:23:23 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

static int	process_heredoc_loop(int hdfd,
								char *delimiter,
								t_dictionary *env)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		ft_printf("herdoc> ");
		line = get_next_line(STDIN_FILENO);
		if (storage_signal(0, 0) != 0)
			return (-1);
		if (!line)
		{
			write(1, "\n", 1);
			break ;
		}
		if (storage_signal(0, 0))
			return (free(line), -1);
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (ft_strcmp(line, delimiter) == 0)
			return (free(line), 0);
		expanded = expand_str(line, env);
		(ft_putstr_fd(expanded, hdfd), ft_putstr_fd("\n", hdfd));
		(free(line), free(expanded));
	}
	return (0);
}

int	here_doc(t_token **stream, t_io_redir *redir, t_dictionary *env)
{
	int		hdfd;
	int		ret;

	(void)stream;
	redir->hd_name = get_hd_name();
	if (!redir->hd_name)
		return (1);
	(signal(SIGINT, handle_sigint_heredoc), signal(SIGQUIT, SIG_IGN));
	hdfd = open(redir->hd_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (hdfd == -1)
		return (free(redir->hd_name), redir->hd_name = NULL, 1);
	ret = process_heredoc_loop(hdfd, redir->filename->text, env);
	close(hdfd);
	(signal(SIGINT, handle_sigint2), signal(SIGQUIT, SIG_IGN));
	if (ret == -1)
	{
		(unlink(redir->hd_name), free(redir->hd_name));
		redir->hd_name = NULL;
		storage_signal(130, 1);
		return (1);
	}
	return (0);
}
