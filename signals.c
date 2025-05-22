/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:59:16 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/22 19:07:12 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"

int	storage_signal(int status, int flag)
{
	static int	signal = 0;

	if (flag)
		signal = status;
	return (signal);
}

void	handle_sigint(int sig)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	storage_signal(128 + sig, 1);
}

int	signals(char **input, int *exit, int argc, char **argv)
{
	int	save_stdin;

	save_stdin = dup(STDIN_FILENO);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
		*input = ft_strdup(argv[2]);
	else
		*input = readline("minishell> ");
	if (!*input)
	{
		ft_printf("exit\n");
		rl_clear_history();
		*exit = 1;
	}
	else if (**input == '\0')
		*input = NULL;
	else if (*input && **input)
		add_history(*input);
	return (save_stdin);
}
