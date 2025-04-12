#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <readline/readline.h>
// # include <editline/readline.h>
#include <readline/history.h> // Include this header for add_history
#include "tokenizer/tokenizer.h"
#include "data_structs/dynamic_array.h"
#include "data_structs/dictionary.h"
#include "libft/include/libft.h"
#include "parser/parser.h"
#include "expansion/expansion.h"
#include "execution/execution.h"
#include "builtins/builtins.h"
#include <signal.h>

//    Get environment
void	get_env(t_dictionary **hash_env, char **env);
int     executor(t_cmd_pipe *sequence, t_dictionary *env, char **main_env);
char    *expand_str(char *str, t_dictionary *env);
void    handle_sigint(int sig);
void    handle_sigquit(int sig);
void    signals(char **input);

#endif