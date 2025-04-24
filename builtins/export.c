#include "../minishell.h"
#include "builtins.h"

// Ojear: env_var = dict_create_entry(env_var_array[0], env_var_array[1]) y dict_insert(&hash_env, env_var)
// tambien split
//void	sort_strings(char **strings, int n) para si me pasan export solo me ordene alfabeticamente el env
// OBJETIVO = export VAR=value
// la variable no puede empezar por algo que no sea letra, lo que continua si, ft_alpha(lib) y puede contener "_"
//valor el que sea?
// si ya existe= VAR+=var, valor nuevo detras del valor old
// que pasa si no existe??

//????????????? env | grep VAR -> nada || pero : export | grep VAR ->  declare -x VAR

//setenv() no está permitida pero se puede recrear

/* 
	-SI pones: $-USER, entonces te expande a 569JNRXZghiklmsUSER Invalido
	-Si poner: export APA$=jesulin, Invalido.
	-Si poners: export apa solo, se genera apa='', pero no se ve en env.
	-Si pones: export apa=, lo mismo del anterior.
	-Si pones: export te saca todo.
	-Si pones: export $#POLLAS=pollas, Invalido.
	-Sipones: export 1234kaka=kaka, te da invalida identifier
	-Si pones export VAR+=var, te lo coje.
	
	Basicamente la diferencia entre VAR= y VAR a secas, es que
	en el primer caso pone ft_strdup(""), mientras que en el 
	segundo ponemos NULL.
*/

#define legal_variable_starter(c) (ISALPHA(c) || (c == '_'))
#define legal_variable_char(c)	(ISALNUM(c) || c == '_')

int	is_valid_name(char *name)
{
	if (!name)
		return (0);
	if (!legal_variable_starter(*name))
		return (0);
	while (*name)
	{
		if (!legal_variable_char(*name))
			return (0);
		name++;
	}
	return (1);
}

void	export_error(char *name)
{
	ft_printf("minishell: export: `%s': not a valid identifier\n", name);
}

int	export(t_exec *exec, char **arguments)
{
	t_dic_entry	*entry;
	char	**var;
	char 	*value;
	char	**env_keys;
	char	*value_for_printing;
	int		status;
	int		i;

	i = -1;
	status = 0;
	if (arguments[1] == NULL)
	{
		env_keys = dict_get_keys(exec->env);
		if (!env_keys)
			return (1);
		sort_strings(env_keys, exec->env->capacity);
		while (env_keys[++i])
		{
			value_for_printing = dict_get(exec->env, env_keys[i]);
			ft_printf("declare -x %s", env_keys[i]);
			if (value_for_printing != NULL)
				ft_printf("=\"%s\"", value_for_printing);
			ft_printf("\n");
		}
		return (0);
	}
	i = 1;
	while (arguments[i])
	{
		var = ft_split(arguments[i], '=');
		if (!var)
			return (1);
		if (is_valid_name(var[0]))
		{
			if (var[1] == NULL && ft_strchr(arguments[i], '='))
				value = "";
			else
				value = var[1];
			entry = dict_create_entry(ft_strdup(var[0]), ft_strdup(value));
			if (ft_strchr(arguments[i], '='))
				entry->export = 1;
			dict_insert(&exec->env, entry);
		}
		else 
		{
			export_error(arguments[i]);
			status = 1;
		}
		ft_free_array(var);
		i++;
	}
	return (status);
}
