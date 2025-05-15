/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:25:57 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/15 21:34:30 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_status(int status, t_dictionary **dict)
{
	if (storage_signal(0,0) != 130) {
		dict_insert(dict, dict_create_entry(ft_strdup("?"), ft_itoa(status)));
		storage_signal(status, 1);
	} else
		storage_signal(0,1);
}

int	main(int argc, char **argv, char **env)
{
	t_darray		*tokens_array;
	char			**tokens_strings;
	t_token			*token_stream;
	char			*line;
	t_dictionary	*hash_env;
	int				saved_stdin;
	int				finish;
	t_token			*tokens_for_free;
	t_cmd_pipe		*sequence;

	line = NULL;
	get_env(&hash_env, env);
	finish = 0;
	(void)argc;
	(void)argv;
	while (1)
	{
		saved_stdin = dup(STDIN_FILENO);
		signals(&line, &finish);
		dict_insert(&hash_env, dict_create_entry(ft_strdup("?"), ft_itoa(storage_signal(0,0))));
		if (finish == 2)
		{
			finish = 0;
			continue ;
		}
		else if (finish == 1)
		{
			finish = 0;
			close(saved_stdin);
			exit(0);
		}
		if (line == NULL)
			continue;
		tokens_array = tokenizer_str(line);
		tokens_strings = (char **)tokens_array->darray;
		token_stream = tokenizer_t_tokens(tokens_strings,
				tokens_array->full_idx);
		ft_free_array(tokens_array->darray);
		tokens_array->darray = NULL;
		free_darray(tokens_array);
		tokens_for_free = token_stream;
		sequence = parse_cmd_pipe(&token_stream, hash_env);
		if (sequence)
			insert_status(executor(sequence, hash_env, env), &hash_env);
		else
			insert_status(2, &hash_env);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
		free_ast(sequence);
		free(tokens_for_free);
	}
	close(saved_stdin);
	dict_delete(hash_env);
	return (0);
}
