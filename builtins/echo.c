/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:57:52 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/14 19:47:32 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	echo(char **arguments)
{
	int		i;
	int		new_line;
	size_t	j;

	i = 0;
	new_line = 1;
	arguments++;
	while (arguments[i] && arguments[i][0] == '-' && arguments[i][1] == 'n')
	{
		j = 1;
		while (arguments[i][j] == 'n')
			j++;
		if (arguments[i][j] != '\0')
			break ;
		new_line = 0;
		i++;
	}
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