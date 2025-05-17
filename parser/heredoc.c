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

int	process_heredoc_loop(int hdfd, char *delimiter, t_dictionary *env)
{
	char	*next_line;
	char	*expanded_line;

	while (1)
	{
		next_line = readline("herdoc> ");
		if (storage_signal(0, 0))
			return (storage_signal(0, 0));
		if (!next_line)
			return (0);
		if (ft_strcmp(next_line, delimiter) == 0)
		{
			free(next_line);
			break ;
		}
		expanded_line = expand_str(next_line, env);
		write(hdfd, expanded_line, ft_strlen(expanded_line));
		(write(hdfd, "\n", 1), free(next_line), free(expanded_line));
	}
	return (0);
}

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

int	here_doc(char *delimiter, t_io_redir *redir, t_dictionary *env)
{
	int		status;
	int		hdfd;

	status = 0;
	signal(SIGINT, handle_sigint_heredoc);
	redir->hd_name = get_hd_name();
	hdfd = open(redir->hd_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (hdfd == -1)
		return (1);
		
	status = process_heredoc_loop(hdfd, delimiter, env);

	close(hdfd);
	return (status);
}
