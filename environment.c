#include "minishell.h"

void	insert_special_params(t_dictionary **env)
{
	t_dic_entry		*env_var;

	env_var = dict_create_entry(ft_strdup("@"), ft_strdup(""));
	dict_insert(env, env_var);
	env_var = dict_create_entry(ft_strdup("*"), ft_strdup(""));
	dict_insert(env, env_var);
	env_var = dict_create_entry(ft_strdup("#"), ft_strdup("0"));
	dict_insert(env, env_var);
	env_var = dict_create_entry(ft_strdup("?"), ft_strdup("0"));
	dict_insert(env, env_var);
	env_var = dict_create_entry(ft_strdup("-"), ft_strdup("himBh"));
	dict_insert(env, env_var);
	env_var = dict_create_entry(ft_strdup("$"), ft_strdup("(missing)"));
	dict_insert(env, env_var);
	env_var = dict_create_entry(ft_strdup("!"), ft_strdup("(missing)"));
	dict_insert(env, env_var);
	env_var = dict_create_entry(ft_strdup("0"), ft_strdup("minishell"));
	dict_insert(env, env_var);
}

void	get_env(t_dictionary **hash_env, char **env)
{
	t_dic_entry		*env_var;
	char			**env_var_array;
	char			*shlvl;

	*hash_env = dict_init(230);
	while (*env)
	{
		env_var_array = ft_split(*env, '=');
		env_var = dict_create_entry(ft_strdup(env_var_array[0]), ft_strdup(env_var_array[1])); //funcion para crear una entrada que se le comparte al dic_insert
		env_var->export = 1;
		ft_free_array(env_var_array);
		dict_insert(hash_env, env_var); // funcion para meter una variable o modificarla si ya existe 
		env++;
	}
	insert_special_params(hash_env);
	shlvl = dict_get(*hash_env, "SHLVL");
	env_var = dict_create_entry(ft_strdup("SHLVL"), ft_itoa(ft_atoi(shlvl) + 1));
	dict_insert(hash_env, env_var);
}

// int main(int argc, char **argv, char **env)
// {
// 	t_dictionary	*hash_env = get_env(env);
// 	printf("user: %s\n", dict_get(hash_env, "USER"));
// }

