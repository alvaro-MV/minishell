/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:58:33 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/14 17:58:34 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../libft/include/libft.h"
#include "builtins.h"
#include <unistd.h>

int	ft_pwd(void)
{
	char	buffer[1024];

	if (getcwd(buffer, sizeof(buffer)))
		ft_printf("%s\n", buffer);
	else
		perror("Error_pwd: too many arguments");
	return (0);
}

int	pwd2(void)
{
	// Llama a la función ft_pwd
	if (ft_pwd() != 0)
	{
		ft_printf("error");
		return (1); // Código de error si ft_pwd falla
	}
	return (0); // Código de éxito si ft_pwd funciona correctamente
}
