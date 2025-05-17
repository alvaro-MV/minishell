/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:58:52 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/17 13:52:00 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../minishell.h"
# include <limits.h>
# include <stddef.h>
# include <unistd.h>

struct					s_exec;
typedef struct s_exec	t_exec;

typedef enum echo_states
{
	INIT = 1,
	PRINT_WORD,
	FLAG
}						t_echo_states;

int						process_flags(char **arguments, int *i);
void					echo(char **arguments);
int						ft_pwd(void);
int						pwd2(void);
int						ft_env(char **args, t_exec *exec);
int						is_valid_name(char *name);
int						legal_variable_starter(int c);
int						legal_variable_char(int c);
void					export_error(char *name);
int						print_exported_vars(t_exec *exec);
int						process_argument(char *argument, t_exec *exec);
int						export(t_exec *exec, char **arguments);
int						is_numeric(const char *str);
int						ft_exit(char **args);
void					remove_env_var(t_exec *exec, char *var_name);
int						unset(t_exec *exec, char **arg);
int						cd(t_exec *exec, char **arg);

#endif