/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:03:16 by alvmoral          #+#    #+#             */
/*   Updated: 2025/02/25 10:43:45 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

int	ft_strncmp(char	*s1, char	*s2, unsigned int n)
{
	if (n == 0)
		return (0);
	if (!s1 && !s2)
		return (1);
	while (*s1 && *s2 && n > 0)
	{
		if (*s1 != *s2)
			return ((unsigned char) *s1 - (unsigned char) *s2);
		s1++;
		s2++;
		n--;
	}
	if (n > 0)
		return ((unsigned char) *s1 - (unsigned char) *s2);
	else
		return (0);
}
