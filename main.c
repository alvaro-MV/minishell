/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:08:03 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/22 19:08:07 by lvez-dia         ###   ########.fr       */
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

void	process_commands(t_dictionary *hash_env, char *line, int *saved_std)
{
	t_minishell	mini;

	mini.tokens_array = tokenizer_str(line);
	mini.saved_std = saved_std;
	mini.tokens_strings = (char **)mini.tokens_array->darray;
	mini.token_stream = tokenizer_t_tokens(mini.tokens_strings,
			mini.tokens_array->full_idx);
	ft_free_array(mini.tokens_array->darray);
	mini.tokens_array->darray = NULL;
	free_darray(mini.tokens_array);
	mini.tokens_for_free = mini.token_stream;
	storage_signal(0, 1);
	mini.env = hash_env;
	mini.sequence = parse_cmd_pipe(&mini.token_stream, mini.env);
	free_tokens(mini.tokens_for_free);
	if (mini.sequence)
		insert_status(executor(&mini, mini.sequence, mini.env), &mini.env);
	else
		insert_status(storage_signal(0, 0), &mini.env);
	free_ast(mini.sequence);
	mini.tokens_array = NULL;
	mini.tokens_strings = NULL;
	mini.tokens_for_free = NULL;
	mini.sequence = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_dictionary	*hash_env;
	char			*line;
	int				finish;
	int				saved_std[2];

	finish = 0;
	init_environment(&hash_env, env, &line, &finish);
	while (1)
	{
		saved_std[0] = signals(&line, &finish, argc, argv);
		saved_std[1] = dup(STDOUT_FILENO);
		if (finish)
		{
			dict_delete(hash_env);
			(close(saved_std[0]), close(saved_std[1]));
			rl_clear_history();
			free(line);
			line = NULL;
			return (0);
		}
		if (!line)
			continue ;
		dict_insert(&hash_env, dict_create_entry(ft_strdup("?"),
				ft_itoa(storage_signal(0, 0))));
		process_commands(hash_env, line, saved_std);
		dup2(saved_std[0], STDIN_FILENO);
		dup2(saved_std[1], STDOUT_FILENO);
		close(saved_std[0]);
		close(saved_std[1]);
		if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
			break ;
	}
	dict_delete(hash_env);
	rl_clear_history();
	free(line);
	return (0);
}
