#ifndef PARSER_H
# define PARSER_H

# include "tokenizer.h"
# include "data_structs/dynamic_array.h"
# include "libft/include/libft.h"

typedef struct	s_io_redir
{
	t_token				*op;
	t_token				*filename;
	struct s_io_redir	*next;
	
}			t_io_redir;

typedef t_darray command;

typedef struct s_cmd 
{
	command			*cmd;
	t_io_redir		*cmd_prefix;
	t_io_redir		*cmd_suffix;
	struct s_cmd	*next;
}					t_cmd;


typedef struct s_cmd_pipe
{
	t_cmd 				*cmd;
	struct s_cmd_pipe	*pipe_seq;
}						t_cmd_pipe;



#endif