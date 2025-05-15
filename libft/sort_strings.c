/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_strings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:59:36 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/15 16:01:40 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

void	sort_strings(char **strings, int n)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - 1)
		{
			if (ft_strcmp(strings[i], strings[j]) < 0)
			{
				temp = strings[i];
				strings[i] = strings[j];
				strings[j] = temp;
			}
			j++;
		}
		i++;
	}
}
