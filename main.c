#include "minishell.h"

void insert_status(int status, t_dictionary **dict)
{
	// ft_pritnf("error: %d     wexit: %s\n", status, WEXITSTATUS(status))
	dict_insert(dict, dict_create_entry(ft_strdup("?"), ft_itoa(WEXITSTATUS(status))));
}

int	main(int argc, char **argv, char **env)
{
	t_darray	*tokens_array;
	char		**tokens_strings;
	t_token		*token_stream;
	char		*line = NULL;
	t_dictionary	*hash_env;

	get_env(&hash_env, env);

	(void)argc;
	(void)argv;
	
	while (1)
	{
		signals(&line); // aqui porque no sabia donde meterlo
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		add_history(line);
		tokens_array = tokenizer_str(line);
		tokens_strings = (char **) tokens_array->darray;
		token_stream = tokenizer_t_tokens(tokens_strings, tokens_array->full_idx);
		t_token	*tokens_for_free = token_stream;
		t_cmd_pipe	*sequence = parse_cmd_pipe(&token_stream);

		if (sequence)
		{
			insert_status(executor(sequence, hash_env, env), &hash_env);
		}

		free(line);
		free_AST(sequence);
		free(tokens_array);
		free(tokens_for_free);
	}
	dict_delete(hash_env);
	return (0);
}
