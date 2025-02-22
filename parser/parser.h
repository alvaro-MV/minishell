#ifndef PARSER_H
# define PARSER_H

# include "../tokenizer/tokenizer.h"
# include "../data_structs/dynamic_array.h"
# include "../libft/include/libft.h"

typedef struct	s_io_redir
{
	t_token				*op;
	t_token				*filename;
	struct s_io_redir	*next;
	// struct s_io_redir	*prev;
	
}			t_io_redir;

typedef t_darray command;

typedef struct s_cmd 
{
	command			*cmd;
	t_io_redir		*cmd_prefix;
	t_io_redir		*cmd_suffix;
	struct s_cmd	*next;
	// struct s_cmd	*prev;
}					t_cmd;


typedef struct s_cmd_pipe
{
	t_cmd 				*cmd;
	struct s_cmd_pipe	*next;
	// struct s_cmd_pipe	*prev;
}						t_cmd_pipe;

// int		here_doc(char *delimiter);

t_cmd_pipe	*parse_cmd_pipe(t_token **token_stream);
t_cmd		*parse_cmd(t_token **token_stream);
t_io_redir	*parse_io_redir(t_token **token_stream);
t_token		*parse_word(t_token **token_stream);

void		free_AST(t_cmd_pipe *sequence);
void		free_cmd(t_cmd *cmd);
void		free_io_redir(t_io_redir *io_redir);
int			add_command(command **cmd, char *element);

#endif