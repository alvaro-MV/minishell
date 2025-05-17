/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:25:57 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/18 00:01:28 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_status(int status, t_dictionary **dict)
{
	if (status || storage_signal(0, 0) != 0)
	{
		dict_insert(dict, dict_create_entry(ft_strdup("?"), ft_itoa(status)));
		storage_signal(status, 1);
	}
	else
		storage_signal(0, 1);
}

void	init_environment(t_dictionary **hash_env, char **env, char **line,
		int *finish)
{
	*line = NULL;
	get_env(hash_env, env);
	*finish = 0;
}

void	process_commands(t_dictionary *hash_env, char *line)
{
	t_darray	*tokens_array;
	char		**tokens_strings;
	t_token		*token_stream;
	t_token		*tokens_for_free;
	t_cmd_pipe	*sequence;

	tokens_array = tokenizer_str(line);
	tokens_strings = (char **)tokens_array->darray;
	token_stream = tokenizer_t_tokens(tokens_strings, tokens_array->full_idx);
	ft_free_array(tokens_array->darray);
	tokens_array->darray = NULL;
	free_darray(tokens_array);
	tokens_for_free = token_stream;
	storage_signal(0, 1);
	sequence = parse_cmd_pipe(&token_stream, hash_env);
	if (sequence)
	{
		insert_status(executor(sequence, hash_env), &hash_env);
		free_ast(sequence);
	}
	else
		insert_status(storage_signal(0, 0), &hash_env);
	// size_t i = 0;
	// while (tokens_for_free[i].type != END)
	// {
	// 	free(tokens_for_free[i].text);
	// 	i ++;
	// }
	free(tokens_for_free);

	tokens_array = NULL;
	tokens_strings = NULL;
	tokens_for_free = NULL;
	sequence = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_minishell		mini;
	t_dictionary	*hash_env;
	char			*line;
	int				finish;

	(void)argc;
	(void)argv;
	finish = 0;
	init_environment(&hash_env, env, &line, &finish);
	while (1)
	{
		signals(&line, &finish);
		if (finish)
			return (dict_delete(hash_env), 0);
		dict_insert(&hash_env, dict_create_entry(ft_strdup("?"),
				ft_itoa(storage_signal(0, 0))));
		process_commands(hash_env, line);
	}
	dict_delete(hash_env);
	return (0);
}
