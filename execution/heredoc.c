#include "execution.h"

int	here_doc(char *delimiter)
{
	char	*next_line;
	int		infd[2];

	pipe(infd);
	if (delimiter[ft_strlen(delimiter)-1] != '\n')
	{
		delimiter = ft_strjoin(delimiter, "\n");
		if (delimiter == NULL)
			return (-1);
	}
	while (1)
	{
		ft_printf("herdoc> ");
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
	dup2(infd[0], 0);
	return (infd[0]);
}

//por que no esta funcionando???