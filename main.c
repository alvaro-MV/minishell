/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:25:57 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/15 18:48:41 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_status(int status, t_dictionary **dict)
{
	dict_insert(dict, dict_create_entry(ft_strdup("?"), ft_itoa(status)));
}

void	init_environment(t_dictionary **hash_env, char **env, char **line,
		int *finish)
{
	*line = NULL;
	get_env(hash_env, env);
	*finish = 0;
}

int	handle_signals(char **line, int *finish)
{
	int	saved_stdin;

	saved_stdin = dup(STDIN_FILENO);
	signals(line, finish);
	if (finish)
	{
		close(saved_stdin);
		exit(0);
	}
	add_history(*line);
	return (saved_stdin);
}

void	process_commands(t_dictionary *hash_env, char **env, char *line)
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
	sequence = parse_cmd_pipe(&token_stream, hash_env);
	if (sequence)
		insert_status(executor(sequence, hash_env, env), &hash_env);
	else
		insert_status(2, &hash_env);
	free_ast(sequence);
	free(tokens_for_free);
}

int	main(int argc, char **argv, char **env)
{
	t_dictionary	*hash_env;
	char			*line;
	int				finish;
	int				saved_stdin;

	(void)argc;
	(void)argv;
	init_environment(&hash_env, env, &line, &finish);
	while (1)
	{
		saved_stdin = handle_signals(&line, &finish);
		process_commands(hash_env, env, line);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	dict_delete(hash_env);
	return (0);
}
