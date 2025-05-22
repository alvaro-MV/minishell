/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:38:04 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/22 23:20:47 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/get_next_line.h"

// char	*take_after_new_line(char *temp)
// {
// 	int		i;
// 	int		j;
// 	char	*dest;

// 	i = 0;
// 	while (temp[i] && temp[i] != '\n')
// 		i++;
// 	if (!temp[i])
// 	{
// 		free(temp);
// 		return (NULL);
// 	}
// 	dest = malloc(sizeof(char) * (ft_strlen(temp) - i + 1));
// 	if (!dest)
// 		return (free(temp), NULL);
// 	j = 0;
// 	while (temp[i])
// 		dest[j++] = temp[++i];
// 	dest[j] = '\0';
// 	free(temp);
// 	return (dest);
// }

// char	*take_until_new_line(char *str)
// {
// 	int		i;
// 	char	*dest;

// 	i = 0;
// 	if (!str[i])
// 		return (NULL);
// 	while (str && str[i] && str[i] != '\n')
// 		i++;
// 	if (str[i] == '\n')
// 		i++;
// 	dest = malloc(sizeof(char) * (i + 1));
// 	if (!dest)
// 		return (NULL);
// 	i = 0;
// 	while (str && str[i] && str[i] != '\n')
// 	{
// 		dest[i] = str[i];
// 		i++;
// 	}
// 	if (str[i] == '\n')
// 		dest[i++] = '\n';
// 	dest[i] = '\0';
// 	return (dest);
// }

// char	*read_until_new_line(int fd, char **str)
// {
// 	char	*buff;
// 	char	*str_tmp;
// 	int		bytes_read;

// 	if (!*str)
// 	{
// 		*str = malloc(1 * sizeof(char));
// 		*str[0] = '\0';
// 	}
// 	if (!*str)
// 		return (NULL);
// 	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
// 	if (!buff)
// 		return (free(*str), NULL);
// 	bytes_read = 1;
// 	while (!ft_strchr(*str, '\n') && bytes_read != 0)
// 	{
// 		bytes_read = read(fd, buff, BUFFER_SIZE);
// 		if (bytes_read == -1)
// 			return (free(buff), free(*str), NULL);
// 		if (bytes_read == 0)
// 			return (free(buff), free(*str), NULL);
// 		buff[bytes_read] = '\0';
// 		str_tmp = *str;
// 		*str = ft_strjoin(*str, buff);
// 		free(str_tmp);
// 		if (!*str)
// 			return (free(buff), NULL);
// 	}
// 	return (free(buff), *str);
// }

// char	*get_next_line(int fd)
// {
// 	static char	*str;
// 	char		*line;

// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	str = read_until_new_line(fd, &str);
// 	if (!str)
// 		return (0);
// 	line = take_until_new_line(str);
// 	if (!line)
// 	{
// 		free(line);
// 		free(str);
// 		str = NULL;
// 		return (NULL);
// 	}
// 	str = take_after_new_line(str);
// 	return (line);
// }

#include "../libft/include/libft.h"
#include <stdlib.h>
#include <unistd.h>

char	*strjoin_and_free(char *s1, char *s2)
{
	char	*joined;
	int		i;
	size_t	j;

	joined = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!joined)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[j])
		joined[i++] = s1[j++];
	j = 0;
	while (s2 && s2[j])
		joined[i++] = s2[j++];
	joined[i] = '\0';
	free(s1);
	return (joined);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static int	buffer_read = 0;
	static int	buffer_pos = 0;
	char		*line;
	char		temp[2];

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (buffer_pos >= buffer_read)
		{
			buffer_read = read(fd, buffer, BUFFER_SIZE);
			buffer_pos = 0;
			if (buffer_read <= 0)
				break ;
		}
		temp[0] = buffer[buffer_pos++];
		temp[1] = '\0';
		line = strjoin_and_free(line, temp);
		if (temp[0] == '\n')
			break ;
	}
	return (line);
}
