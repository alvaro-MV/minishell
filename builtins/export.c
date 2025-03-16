#include "../minishell.h"
/* 
	-SI pones: $-USER, entonces te expande a 569JNRXZghiklmsUSER Invalido
	-Si poner: export APA$=jesulin, no saca mensaje y no crea la variable
	-Si poners: export apa solo, se genera apa='', pero no se ve en env.access
	-Si pones: export apa=, lo mismo del anterior.
	-Si pones: export 
*/
int	is_valid_name(char *name)
{
	while (*name)
	{
		if (!ft_isalpha(*name))
			return (0);
		name++;
	}
	return (1);
}

void	export(t_exec *exec)
{
	t_dic_entry	*entry;
	char	**arguments;
	char	**var;
	char	**env_keys;
	int		i;
	int		j;

	i = 0;
	arguments = (char **) exec->cmd->cmd->darray;
	if (arguments[1] == NULL)
	{
		env_keys = dict_get_keys(exec->cmd);
		sort_strings(env_keys, exec->env->capacity);
		while (env_keys[i])
			ft_printf("%s\n", env_keys[i++]);
		return ;
	}
	while (arguments[i])
	{
		if (ft_strchr(arguments[i], '=') 
			&& !ft_strchr(ft_strchr(arguments[i], '='), '='))
		{
			var = ft_split(arguments[i], '=');
			if (is_valid_name(var[0]))
			{
				entry = dict_create_entry(var[0], var[1]);
				dict_insert(&exec->env, entry);
			}
		}
		i++;
	}
}
