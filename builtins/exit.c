#include "builtins.h"

// OBJETIVO = exit 0

//exit()

//ft_isdigit

// propia función

int is_numeric(const char *str)
{
    int i;

    i = 0;
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}


int ft_exit(char **args)
{
    int status;

    if (!args[1])
        exit(0);
    if (!is_numeric(args[1]))
    {
        ft_printf("exit: %s: numeric argument required\n", args[1]);
        exit(255);
    }
    if (args[2])
    {
        ft_printf("exit: too many arguments\n");
        return (1);
    }
    else
        exit(0);
    status = ft_atoi(args[1]);
    exit(status);
    return (0);
}

/*          - obtener el comando ingresado por el usuario
            - si existe el comando despues del exit 
                - si no hay sale por 0
            - si existe argumento despues del exit 
                - comprueba si es numero 
                - si no imprime error y salida por 255
            - si existe el argumento 
                - pero hay mas argumentos imprime error y sale por la 1 
                - si hay mas de un argumento
                    - imprime error y sale por 1
            - convierte el argumento a numero y sale con ese estado
*/