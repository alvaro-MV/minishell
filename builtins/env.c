#include "builtins.h"

int	ft_env(char **args, char **environment)
{
    if (args[0] && args[1] == NULL)
    {
        while (*environment != NULL)
        {
            ft_printf("%s\n", *environment);
            environment++;
        }
    }
    else
    {
        ft_printf("too much arguments\n");
        return (1);
    }
    return (0); 
}