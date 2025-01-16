#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	**ft_split(char const *s, char c);

int	main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;

	t_dictionary	*hash_env;
	t_dic_entry		*env_var;
	char			**env_var_array;

	hash_env = dict_init(16); //El número de variables que hay en la gramática de shell
	while (*env)
	{
		env_var_array = ft_split(*env, '=');
		env_var = dict_create_entry(env_var_array[0], env_var_array[1]);
		dict_insert(&hash_env, env_var);
		env++;
	}
	printf("WAYLAND_DISPLAY=%s\n", dict_get(hash_env, "WAYLAND_DISPLAY"));
	printf("SHELL=%s", dict_get(hash_env, "SHELL"));
	return (0);
}