//#include "builtins.h"
#include <unistd.h>
#include "../libft/include/libft.h"
// OBJETIVO = pwd


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

int	ft_pwd(void)
{
	char	buffer[1024];

	if (getcwd(buffer, sizeof(buffer)))
		ft_printf("%s\n", buffer);
	// else
	// 	perror("Error_pwd: too many arguments");
	return (0);
}
