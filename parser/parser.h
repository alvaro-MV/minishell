#ifndef PARSER_H
# define PARSER_H

# include "../data_structs/dictionary.h"
# include "../data_structs/dynamic_array.h"
# include "../expansion/expansion.h"
# include "../libft/include/libft.h"
# include "../tokenizer/tokenizer.h"
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <wait.h>

typedef struct s_io_redir
{
	t_token				*op;
	t_token				*filename;
	struct s_io_redir	*next;
	int					fd;

}						t_io_redir;

typedef t_darray		command;

typedef struct s_cmd
{
	command				*cmd;
	t_io_redir			*cmd_prefix;
	t_io_redir			*cmd_suffix;
	struct s_cmd		*next;
	int					fds[2];
}						t_cmd;

typedef struct s_cmd_pipe
{
	t_cmd				*cmd;
	struct s_cmd_pipe	*next;
}						t_cmd_pipe;

t_cmd_pipe				*parse_cmd_pipe(t_token **token_stream,
							t_dictionary *env);
t_cmd					*parse_cmd(t_token **token_stream, t_dictionary *env);
t_io_redir				*parse_io_redir(t_token **token_stream,
							t_dictionary *env);
t_token					*parse_word(t_token **token_stream);

void					free_ast(t_cmd_pipe *sequence);
void					free_cmd(t_cmd *cmd);
void					free_io_redir(t_io_redir *io_redir);
int						add_command(command **cmd, char *el, t_dictionary *env,
							int exp);
void					here_doc(char *delimiter, t_io_redir *redir,
							t_dictionary *env);

#endif