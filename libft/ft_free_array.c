/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:56:00 by alvmoral          #+#    #+#             */
/*   Updated: 2025/05/17 12:35:20 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

void	ft_free_array(char **marr)
{
	char			*free_ptr;
	unsigned int	i;

	i = 0;
	while (marr[i])
	{
		free_ptr = marr[i];
		i++;
		free(free_ptr);
	}
	free(marr);
}
