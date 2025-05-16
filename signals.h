/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:59:08 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/16 16:11:07 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "libft/include/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <unistd.h>

void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	signals(char **input, int *exit);
int		storage_signal(int status, int flag);

#endif