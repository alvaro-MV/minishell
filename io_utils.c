#include "libft/include/libft.h"
#include "libft/include/get_next_line.h"
#include <unistd.h>

int	here_doc(char *delimiter)
{
	char *next_line;
	int infd[2];

	if (pipe(infd) == -1)
		return (-1);
	if (delimiter[ft_strlen(delimiter) - 1] != '\n')
	{
		delimiter = ft_strjoin(delimiter, "\n");
		if (delimiter == NULL)
			return (-1);
	}
	while (1)
	{
		ft_printf("\033[3;34m > \033[0m");
		next_line = get_next_line(0);
		if (ft_strcmp(next_line, delimiter) == 0)
		{
			free(next_line);
			break ;
		}
		write(infd[1], next_line, ft_strlen(next_line));
		free(next_line);
	}
	free(delimiter);
	close(infd[1]);
	return (infd[0]);
}
