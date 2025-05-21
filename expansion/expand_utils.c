/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:10:58 by alvmoral          #+#    #+#             */
/*   Updated: 2025/05/21 20:06:28 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

int	is_env_var(char *str, t_utils utils)
{
	return ((str[utils.i] == '$' && ft_isalnum(str[utils.i + 1]))
		|| (str[utils.i] == '$' && str[utils.i + 1] == '\'')
		|| (str[utils.i] == '$' && str[utils.i + 1] == '"')
		|| (str[utils.i] == '$' && str[utils.i + 1] == '_')
		|| (str[utils.i] == '$' && is_special_var(&str[utils.i + 1])));
}

int	is_for_expand_str(char *str)
{
	if (!ft_strchr(str, '"') && !ft_strchr(str, '\'') && !ft_strchr(str, '$'))
		return (0);
	return (1);
}

void	join_char(char **expanded_str, char *str)
{
	char	*tmp_str;
	char	c[2];

	tmp_str = *expanded_str;
	c[0] = *str;
	c[1] = '\0';
	*expanded_str = ft_strjoin(*expanded_str, c);
	free(tmp_str);
}

int	is_special_var(char *var)
{
	if (!ft_strncmp(var, "?", 1) || !ft_strncmp(var, "0", 1))
		return (1);
	return (0);
}
