/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:59:16 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/15 15:55:39 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
	(void)sig;
}

void	signals(char **input, int *exit)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	if (1)
	{
		*input = readline("minishell> ");
		if (!*input)
		{
			ft_printf("exit\n");
			*exit = 1;
		}
		if (*input && **input)
			add_history(*input);
	}
}
