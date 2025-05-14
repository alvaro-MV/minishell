/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:59:16 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/14 21:24:39 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "signals.h"

// handle_sigint_child()
// {
	
// }

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);// Imprimir una nueva línea
	rl_on_new_line();// Preparar readline para mostrar el prompt en una nueva línea
	rl_replace_line("", 0);// Limpiar la línea actual
	rl_redisplay();// Mostrar el nuevo prompt
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
