/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:56:00 by alvmoral          #+#    #+#             */
/*   Updated: 2025/05/21 12:49:35 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

void	ft_free_array(char **marr)
{
	char			*free_ptr;
	unsigned int	i;

	i = 0;
	if (marr == NULL)
		return ;
	while (marr[i])
	{
		free_ptr = marr[i];
		i++;
		free(free_ptr);
	}
	free(marr);
}
