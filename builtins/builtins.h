/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:58:52 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/14 17:58:53 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BUILTINS_H
# define BUILTINS_H

# include "../minishell.h"
# include <stddef.h>
# include <unistd.h>

struct	s_exec;
typedef struct s_exec	t_exec;

typedef enum echo_states
{
	INIT = 1,
	PRINT_WORD,
	FLAG
}						t_echo_states;

void					echo(char **arguments);
int						pwd2(void);
int						ft_env(char **args, t_exec *exec);
int						is_valid_name(char *name);
void					export_error(char *name);
int						export(t_exec *exec, char **arguments);
int						is_numeric(const char *str);
int						ft_exit(char **args);
int						unset(t_exec *exec, char **arg);
int						cd(t_exec *exec, char **arg);

#endif