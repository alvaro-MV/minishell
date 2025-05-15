/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:01:07 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/15 20:31:29 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "builtins/builtins.h"
# include "data_structs/dictionary.h"
# include "data_structs/dynamic_array.h"
# include "execution/execution.h"
# include "expansion/expansion.h"
# include "libft/include/libft.h"
# include "parser/parser.h"
# include "signals.h"
# include "tokenizer/tokenizer.h"
# include <readline/history.h>

void	get_env(t_dictionary **hash_env, char **env);
int		executor(t_cmd_pipe *sequence, t_dictionary *env, char **main_env);
char	*expand_str(char *str, t_dictionary *env);
void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	insert_special_params(t_dictionary **env);
char	**dict_envp(t_dictionary *env, unsigned int index, int j);
void	dict_set_env_var(t_dictionary **env, char *k, char *v, int export);

#endif