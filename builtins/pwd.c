//#include "builtins.h"
#include <unistd.h>
#include "../libft/include/libft.h"
// OBJETIVO = pwd


/*int	ft_exec_pwd(env)
{
	char	*buffer[1024];
	char	*actual_directory;
    //CREAR buffer para almacenar el directorio actual (tamaño 1024)

    // Intentar obtener el directorio actual con getcwd()
	//SI getcwd(buffer, tamaño_buffer) es exitoso:
    //IMPRIMIR buffer seguido de un salto de línea
    //DEVOLVER éxito (0)
	if (getcwd(buffer, sizeof(buffer)) == 0)
	{
		ft_printf("%d\n", buffer);
		return (0);
	}// int		main(int argc, char **argv, char **env);
	else
	{
		perror("Error_pwd: too many arguments");
		return (0);
	}
    // Manejar el caso en el que getcwd() falla
    IMPRIMIR mensaje de error usando perror()

    // Buscar PWD en las variables de entorno
    ITERAR por cada entrada en env:
        SI la entrada COMIENZA con "PWD=":
            IMPRIMIR el valor de PWD seguido de un salto de línea
            DEVOLVER éxito (0)

    // Si PWD no está definido, devolver un error
    IMPRIMIR "Error: PWD not found" en stderr
    DEVOLVER código de error (1)
}*/






// getcwd()

// solo un alrgumento == pwd : entra, else maaal


// gestion errores

// int ft_pwd(void);

// int main(void)
// {
//     // Llama a la función ft_pwd
//     if (ft_pwd() != 0)
//     {
//         ft_printf("error");
//         return (1); // Código de error si ft_pwd falla
//     }
//     return (0); // Código de éxito si ft_pwd funciona correctamente
// }

// int	ft_pwd(void)
// {
// 	char	buffer[1024];

// 	if (getcwd(buffer, sizeof(buffer)))
// 		ft_printf("%s\n", buffer);
// 	else
// 		perror("Error_pwd: too many arguments");
// 	return (0);
// }
