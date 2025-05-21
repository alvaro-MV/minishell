/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:04:37 by alvmoral          #+#    #+#             */
/*   Updated: 2025/05/21 20:13:19 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void	no_se_pon_nombre_2(char *str, t_utils *utils, t_dictionary *env)
{
	char	*tmp_str;
	char	*env_var_name;
	char	*env_var_value;
	char	*trimmed_var;

	trimmed_var = NULL;
	env_var_value = NULL;
	tmp_str = utils->expanded_str;
	env_var_name = ft_substr(str, utils->i, utils->len_env_var - utils->i);
	if (!env_var_name)
		return (free(tmp_str), free(utils->expanded_str));
	trimmed_var = ft_strtrim(env_var_name, " \t\r");
	if (ft_strncmp(trimmed_var, " ", 2))
	{
		env_var_value = dict_get(env, env_var_name);
		if (!env_var_value)
			env_var_value = "";
	}
	free(trimmed_var);
	utils->expanded_str = ft_strjoin(utils->expanded_str, env_var_value);
	utils->i = (free(tmp_str), free(env_var_name), utils->len_env_var - 1);
}

int	nose_pon_nombre(t_dictionary *env, char *str, t_utils *utils)
{
	if (utils->state == ENV_VAR)
	{
		utils->state = utils->old_state;
		utils->old_state = ENV_VAR;
		utils->len_env_var = utils->i;
		if (utils->state != DOUBLE_QUOTE && str[utils->i] == '\'')
			utils->state = SINGLE_QUOTE;
		else
		{
			if (is_special_var(&str[utils->len_env_var]))
				utils->len_env_var++;
			else if (!is_special_var(&str[utils->len_env_var]))
			{
				while (ft_isalnum(str[utils->len_env_var]) || str[utils->len_env_var] == '_')
				{
					if (!ft_isalpha(str[utils->i]) && str[utils->i] != '_')
						break ;
					utils->len_env_var++;
				}
			}
			no_se_pon_nombre_2(str, utils, env);
		}
		return (1);
	}
	return (0);
}

int	expand_quotes(char *str, t_utils *utils)
{
	if (utils->state == DOUBLE_QUOTE)
	{
		utils->old_state = utils->state;
		if (str[utils->i] == '"')
			utils->state = WORD;
		else if ((str[utils->i] == '$' && ft_isalpha(str[utils->i + 1]))
			|| (str[utils->i] == '$' && is_special_var(&str[utils->i + 1]))
			|| (str[utils->i] == '$' && str[utils->i + 1 ] == '_'))
			utils->state = ENV_VAR;
		else
			join_char(&utils->expanded_str, &str[utils->i]);
		return (1);
	}
	else if (utils->state == SINGLE_QUOTE)
	{
		utils->old_state = utils->state;
		if (str[utils->i] == '\'')
			utils->state = WORD;
		else
			join_char(&utils->expanded_str, &str[utils->i]);
		return (1);
	}
	return (0);
}

char	*expand_str(char *str, t_dictionary *env)
{
	t_utils	utils;

	utils = ((void)env, (t_utils){0});
	utils.expanded_str = ft_strdup("");
	utils.state = WORD;
	utils.old_state = WORD;
	while (str[utils.i])
	{
		if (utils.state == WORD)
		{
			utils.old_state = utils.state;
			if (str[utils.i] == '"')
				utils.state = DOUBLE_QUOTE;
			else if (str[utils.i] == '\'')
				utils.state = SINGLE_QUOTE;
			else if (is_env_var(str, utils))
				utils.state = ENV_VAR;
			else
				join_char(&utils.expanded_str, &str[utils.i]);
		}
		else if (!expand_quotes(str, &utils))
			nose_pon_nombre(env, str, &utils);
		utils.i++;
	}
	return (utils.expanded_str);
}
