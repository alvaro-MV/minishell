#include "builtins.h"

void	echo(char	**arguments)
{
	int			i;
	size_t		j;
	int			new_line;
	echo_states	e_states;

	i = 0;
	j = 0;
	new_line = 1;
	e_states = INIT;
	arguments++;
	while (arguments[i])
	{
		if (e_states == INIT)
		{
			if (!ft_strncmp(arguments[i], "-", 1))
				e_states = FLAG;
			else
				e_states = PRINT_WORD;
		}
		if (e_states == FLAG)
		{
			if (arguments[i][0] == '-' && arguments[i][1] != 'n')
			{
				if (arguments[i][1] == '\0')
					i++;
				e_states = PRINT_WORD;
				continue ;
			}
			j = 1;
			while (arguments[i][j])
			{
				if (arguments[i][j] != 'n')
					break ;
				j++;
			}
			if (j == ft_strlen(arguments[i]) && arguments[i][0] == '-')
				new_line = 0;
			else
			{
				ft_printf("%s ", arguments[i]);
				e_states = PRINT_WORD;
			}
		}
		else if (e_states == PRINT_WORD)
			ft_printf("%s ", arguments[i]);
		i++;
	}
	if (new_line)
		write(1, "\n", 1);
}

// int	main(void)
// {
// 	// echo(ft_split("echo -nnnn -n 3", ' '));
// 	// echo(ft_split("echo -nnnn  3 -n 3", ' '));
// 	// echo(ft_split("echo --nnnn  3 -n 3", ' '));
// 	// echo(ft_split("echo -n --nnnn  3 -n 3", ' '));
// 	// echo(ft_split("echo - 4", ' '));
// 	echo(ft_split("echo - - -", ' '));
// }
