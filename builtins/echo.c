#include "builtins.h"
// #include <stddef.h>
// #include <unistd.h>
// #include "../libft/include/libft.h"

void	echo(char **arguments)
{
	int		i;
	int		new_line;
	// char	*trim_arg;
	size_t	j;

	i = 0;
	// trim_arg = NULL;
	new_line = 1;
	arguments++;
	// Detectar flags (-n)
	while (arguments[i] && (arguments[i][0] == '-' || isspace(arguments[i][0])))
	{
		j = 0;
		while (arguments[i][j])
		{
			if (arguments[i][j] == '-' && arguments[i][j + 1] == 'n')
				j++;
			if (!isspace(arguments[i][j]) && arguments[i][j] != '-'
				&& arguments[i][j] != 'n')
				break ; 
			j++;
		}
		if (arguments[i][j] != '\0')
			break ;
		new_line = 0;
		// j = 0;
		// free(trim_arg);
		// trim_arg = ft_strtrim(arguments[i], " \t\r");
		// if (trim_arg[0] != '-')
		// 	break ;
		// j++;
		// while (trim_arg[j] == 'n') // Comprobar que todo sean 'n'
		// 	j++;
		// if (trim_arg[j] != '\0') // Si hay algo más, no es un flag válido
		// 	break ;
		// new_line = 0; // Desactivar salto de línea
		i++;
	}
	// free(trim_arg);
	// Imprimir los argumentos restantes
	while (arguments[i])
	{
		ft_printf("%s", arguments[i]);
		if (arguments[i + 1]) // Evitar el espacio final
			ft_printf(" ");
		i++;
	}
	// Imprimir salto de línea si es necesario
	if (new_line)
		write(1, "\n", 1);
}


// void	echo(char	**arguments)
// {
// 	int			i;
// 	size_t		j;
// 	int			new_line;
// 	echo_states	e_states;

// 	i = 0;
// 	j = 0;
// 	new_line = 1;
// 	e_states = INIT;
// 	arguments++;
// 	while (arguments[i])
// 	{
// 		if (e_states == INIT)
// 		{
// 			if (!ft_strncmp(arguments[i], "-", 1))
// 				e_states = FLAG;
// 			else
// 				e_states = PRINT_WORD;
// 		}
// 		if (e_states == FLAG)
// 		{
// 			if (arguments[i][0] == '-' && arguments[i][1] != 'n')
// 			{
// 				if (arguments[i][1] == '\0')
// 					i++;
// 				e_states = PRINT_WORD;
// 				continue ;
// 			}
// 			j = 1;
// 			while (arguments[i][j])
// 			{
// 				if (arguments[i][j] != 'n')
// 					break ;
// 				j++;
// 			}
// 			if (j == ft_strlen(arguments[i]) && arguments[i][0] == '-')
// 				new_line = 0;
// 			else
// 			{
// 				ft_printf("%s ", arguments[i]);
// 				e_states = PRINT_WORD;
// 			}
// 		}
// 		else if (e_states == PRINT_WORD)
// 			ft_printf("%s ", arguments[i]);
// 		i++;
// 	}
// 	if (new_line)
// 		write(1, "\n", 1);
// }

/*int	main(void)
{
	echo(ft_split("echo -nnnn -n 3", ' '));
	echo(ft_split("echo -nnnn  3 -n 3", ' '));
	echo(ft_split("echo --nnnn  3 -n 3", ' '));
	echo(ft_split("echo -n --nnnn  3 -n 3", ' '));
	echo(ft_split("echo - 4", ' '));
	echo(ft_split("echo - - -", ' '));
}*/


/*Comando				Salida esperada
echo hola mundo		hola mundo seguido de un salto de línea.
echo -n hola mundo	hola mundo sin salto de línea.
echo -nnn hola		hola sin salto de línea.
echo -x hola		-x hola con salto de línea.
echo "hola mundo"	hola mundo con salto de línea.
echo "hola" "mundo"	hola mundo con salto de línea.*/