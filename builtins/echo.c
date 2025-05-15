/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:57:52 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/15 15:46:43 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	process_flags(char **arguments, int *i)
{
	int		new_line;
	size_t	j;

	new_line = 1;
	while (arguments[*i] && arguments[*i][0] == '-' && arguments[*i][1] == 'n')
	{
		j = 1;
		while (arguments[*i][j] == 'n')
			j++;
		if (arguments[*i][j] != '\0')
			break ;
		new_line = 0;
		(*i)++;
	}
	return (new_line);
}

void	echo(char **arguments)
{
	int		i;
	int		new_line;

	i = 0;
	new_line = process_flags(arguments, &i);
	arguments++;
	while (arguments[i])
	{
		ft_printf("%s", arguments[i]);
		if (arguments[i + 1])
			ft_printf(" ");
		i++;
	}
	if (new_line)
		write(1, "\n", 1);
}
