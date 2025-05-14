/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:13:52 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/14 18:18:44 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

int	is_for_expand_str(char *str)
{
	if (!ft_strchr(str, '"') && !ft_strchr(str, '\'') && !ft_strchr(str, '$'))
		return (0);
	return (1);
}

void	join_char(char **expanded_str, char *str)
{
	char	*tmp_str;
	char 	c[2];

	tmp_str = *expanded_str;
	c[0] = *str;
	c[1] = '\0';
	*expanded_str = ft_strjoin(*expanded_str, c);
	free(tmp_str);
}

static int is_special_var(char *var)
{
	if (!ft_strncmp(var, "?", 1)
		|| !ft_strncmp(var, "0", 1))
		return (1);
	return (0);
}

char	*expand_str(char *str, t_dictionary *env)
{
	int				i;
	char			*expanded_str;
	char			*tmp_str;
	t_expand_states	state;
	t_expand_states	old_state;
	int		len_env_var;
	char	*env_var_name;
	char	*env_var_value;

	char	*trimmed_var = NULL;
	i = 0;
	expanded_str = ft_strdup("");
	state = WORD;
	old_state = WORD;
	while (str[i])
	{
		if (state == WORD)
		{
			old_state = state;
			if (str[i] == '"')
				state = DOUBLE_QUOTE;
			else if (str[i] == '\'')
				state = SINGLE_QUOTE;
			else if ((str[i] == '$' && ft_isalnum(str[i + 1]))
					|| (str[i] == '$' && str[i + 1] == '\'')
					|| (str[i] == '$' && str[i + 1] == '"')
					|| (str[i] == '$' && is_special_var(&str[i + 1])))
				state = ENV_VAR;
			else
				join_char(&expanded_str, &str[i]);
		}
		else if (state == DOUBLE_QUOTE)
		{
			old_state = state;
			if (str[i] == '"')
				state = WORD;
			else if ((str[i] == '$' && ft_isalpha(str[i + 1]))
					|| (str[i] == '$' && is_special_var(&str[i + 1])))
				state = ENV_VAR;
			else
				join_char(&expanded_str, &str[i]);
		}
		else if (state == SINGLE_QUOTE)
		{
			old_state = state;
			if (str[i] == '\'')
				state = WORD;
			else
				join_char(&expanded_str, &str[i]);
		}
		else if (state == ENV_VAR)
		{
			state = old_state;
			old_state = ENV_VAR;
			len_env_var = i;
			if (state != DOUBLE_QUOTE && str[i] == '\'')
			{
				// i--;
				state = SINGLE_QUOTE;
			}
			else
			{
				if (is_special_var(&str[len_env_var]))
					len_env_var++;
				else
				{
					while (ft_isalnum(str[len_env_var]))
					{
						len_env_var++;
						if (!ft_isalpha(str[i]))
							break ;
					}
				}
				tmp_str = expanded_str;
				env_var_name = ft_substr(str, i, len_env_var - i);
				if (!env_var_name)
					return (free(tmp_str), free(expanded_str), NULL);
				trimmed_var = ft_strtrim(env_var_name, " \t\r");
				if (ft_strncmp(trimmed_var, " ", 2))
				{
					env_var_value = dict_get(env, env_var_name);
					if (!env_var_value)
						env_var_value = "";
				}
				free(trimmed_var);
				expanded_str = ft_strjoin(expanded_str, env_var_value);
				free(tmp_str);
				free(env_var_name);
				i = len_env_var - 1;
			}
		}
		i++;
	}
	return (expanded_str);
}
