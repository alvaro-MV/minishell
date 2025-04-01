#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_darray	*tokens_array;
	char		**tokens_strings;
	t_token		*token_stream;
	char		*line = NULL;
	
	t_dictionary	*hash_env = get_env(env);

	(void)argc;
	(void)argv;
	while ((line = readline("> ")))
	{
		add_history(line);
		tokens_array = tokenizer_str(line);
		tokens_strings = (char **) tokens_array->darray;
		token_stream = tokenizer_t_tokens(tokens_strings, tokens_array->full_idx);
		t_token	*tokens_for_free = token_stream;

		t_cmd_pipe	*sequence = parse_cmd_pipe(&token_stream);
		if (sequence)
		{
			executor(sequence, hash_env, env);
		}

		free(line);
		free_AST(sequence);
		free(tokens_array);
		free(tokens_for_free);
	}
	// dict_delete(hash_env);
	return (0);
}
