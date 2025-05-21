/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:59:08 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/21 12:04:27 by alvaro           ###   ########.fr       */
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
int		signals(char **input, int *exit, int argc, char **argv);
int		storage_signal(int status, int flag);

#endif