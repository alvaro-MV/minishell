#ifndef SIGNALS_H
# define SIGNALS_H


# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h> 
# include <unistd.h>
# include "libft/include/libft.h"

extern volatile sig_atomic_t g_sigint_received;

void handle_sigint(int sig);
void handle_sigquit(int sig);
void signals(char **input, int *exit);

#endif