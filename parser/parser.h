/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:55:02 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/17 20:00:47 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../data_structs/dictionary.h"
# include "../data_structs/dynamic_array.h"
# include "../expansion/expansion.h"
# include "../libft/include/libft.h"
# include "../signals.h"
# include "../tokenizer/tokenizer.h"
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <wait.h>

typedef struct s_io_redir
{
	t_token				*op;
	char				*hd_name;
	t_token				*filename;
	struct s_io_redir	*next;
	int					fd;
}						t_io_redir;

typedef t_darray		t_command;

typedef struct s_cmd
{
	t_command			*cmd;
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

void					free_io_redir(t_io_redir *io_redir);
void					free_cmd(t_cmd *cmd);
void					free_ast(t_cmd_pipe *sequence);
void					handle_sigint2(int sig);
void					handle_sigquit2(int sig);
void					handle_sigint_heredoc(int sig);
int						process_heredoc_loop(int hdfd, char *delimiter,
							t_dictionary *env);
int						here_doc(char *delimiter, t_io_redir *redir,
							t_dictionary *env);
int						parse_ix(t_io_redir **ptr_io_redir,
							t_token **token_stream, t_dictionary *env);
int						fill_cmd(t_token **stream, t_command **ptr_cmd,
							t_dictionary *env);
t_cmd					*init_cmd_parsing(t_token **token_stream);
t_cmd					*parse_cmd(t_token **token_stream, t_dictionary *env);
int						alloc_io_redir(t_io_redir **ptr__io_redir);
t_io_redir				*parse_io_redir(t_token **token_stream,
							t_dictionary *env);
int						is_empty_cmd(t_cmd *cmd);
int						alloc_pipe_cmd(t_cmd_pipe **ptr_cmd_pipe);
t_cmd_pipe				*parse_cmd_pipe(t_token **token_stream,
							t_dictionary *env);
t_token					*parse_word(t_token **token_stream);
int						handle_expansion(t_command **cmd, char *element,
							t_dictionary *env);
int						add_command(t_command **cmd, char *element,
							t_dictionary *env, int exp);
void					print_from_diff(char *AST, char *expected);
void					print_io_redir(t_io_redir *io_redir);
void					print_io_redirections(t_cmd *cmd);
void					print_cmd(t_cmd *cmd);
void					print_ast(t_cmd_pipe *sequence);

#endif