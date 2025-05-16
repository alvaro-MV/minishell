/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:31:13 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/16 17:31:47 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
