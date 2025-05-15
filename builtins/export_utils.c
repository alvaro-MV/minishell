/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:41:21 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/15 16:42:21 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	legal_variable_starter(int c)
{
	return (ft_isalpha(c) || c == '_');
}

int	legal_variable_char(int c)
{
	return (ft_isalnum(c) || c == '_');
}

int	is_valid_name(char *name)
{
	if (!name)
		return (0);
	if (!legal_variable_starter(*name))
		return (0);
	while (*name)
	{
		if (!legal_variable_char(*name))
			return (0);
		name++;
	}
	return (1);
}
