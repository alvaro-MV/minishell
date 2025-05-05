#include "minishell.h"

void insert_status(int status, t_dictionary **dict)
{
	dict_insert(dict, dict_create_entry(ft_strdup("?"), ft_itoa(status)));
}

int	main(int argc, char **argv, char **env)
{
	t_darray		*tokens_array;
	char			**tokens_strings;
	t_token			*token_stream;
	char			*line = NULL;
	t_dictionary	*hash_env;
	int 			saved_stdin;
	int				finish;

	get_env(&hash_env, env);
	finish = 0;
	(void)argc;
	(void)argv;

	
	while (1)
	{
		saved_stdin = dup(STDIN_FILENO);
		signals(&line, &finish); // aqui porque no sabia donde meterlo
		if (finish)
		{
			close(saved_stdin);
			exit(0);
		}
		if (*line == '\0')
		{
			free(line);
			continue ;
		}

		add_history(line);
		tokens_array = tokenizer_str(line);
		tokens_strings = (char **) tokens_array->darray;
		token_stream = tokenizer_t_tokens(tokens_strings, tokens_array->full_idx);
		ft_free_array(tokens_array->darray);
		tokens_array->darray = NULL;
		free_darray(tokens_array);
		t_token	*tokens_for_free = token_stream;
		t_cmd_pipe	*sequence = parse_cmd_pipe(&token_stream, hash_env);

		if (sequence)
			insert_status(executor(sequence, hash_env, env), &hash_env);
		else
			insert_status(2, &hash_env);

    	dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
		free_AST(sequence);
		free(tokens_for_free);
	}
	close(saved_stdin);
	dict_delete(hash_env);
	return (0);
}
