#include "minishell.h"

void	insert_special_params(t_dictionary **env)
{
	t_dic_entry		*env_var;

	env_var = dict_create_entry("@", "");
	dict_insert(env, env_var);
	env_var = dict_create_entry("*", "");
	dict_insert(env, env_var);
	env_var = dict_create_entry("#", "0");
	dict_insert(env, env_var);
	env_var = dict_create_entry("?", "0");
	dict_insert(env, env_var);
	env_var = dict_create_entry("-", "himBh");
	dict_insert(env, env_var);
	env_var = dict_create_entry("$", "(missing)");
	dict_insert(env, env_var);
	env_var = dict_create_entry("!", "(missing)");
	dict_insert(env, env_var);
	env_var = dict_create_entry("0", "minishell");
	dict_insert(env, env_var);
}

t_dictionary	*get_env(char **env)
{
	t_dictionary	*hash_env;
	t_dic_entry		*env_var;
	char			**env_var_array;

	hash_env = dict_init(23);
	while (*env)
	{
		env_var_array = ft_split(*env, '=');
		env_var = dict_create_entry(env_var_array[0], env_var_array[1]);
		dict_insert(&hash_env, env_var);
		env++;
	}
	insert_special_params(&hash_env);
	return (hash_env);
}

// int main(int argc, char **argv, char **env)
// {
// 	t_dictionary	*hash_env = get_env(env);
// 	printf("user: %s\n", dict_get(hash_env, "USER"));
// }

