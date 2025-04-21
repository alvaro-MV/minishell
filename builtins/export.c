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

//  aflags = 0;
// 	  if (assign)
// 	    {
// 	      name[assign] = '\0';
// 	      if (name[assign - 1] == '+')
// 		{
// 		  aflags |= ASS_APPEND;
// 		  name[assign - 1] = '\0';
// 		}
// 	    }

// 	  if (legal_identifier (name) == 0)
// 	    {
// 	      sh_invalidid (name);
// 	      if (assign)
// 		assign_error++;
// 	      else
// 		any_failed++;
// 	      list = list->next;
// 	      continue;
// 	    }
// if (assign)	/* xxx [-np] name=value */
// 	    {
// 	      name[assign] = '=';
// 	      if (aflags & ASS_APPEND)
// 		name[assign - 1] = '+';
// 	if (do_assignment_no_expand (name) == 0)
// 		assign_error++;
// 	      name[assign] = '\0';
// 	      if (aflags & ASS_APPEND)
// 		name[assign - 1] = '\0';
// }

int	is_valid_name(char *name)
{
	if (legal_variable_starter(*name))
		return (1);
	while (*name)
	{
		if (legal_variable_char(*name))
			return (1);
		name++;
	}
	return (0);
}

void	export_error(char *name)
{
	ft_printf("minishell: export: `%s': not a valid identifier\n", name);
}

void	export(t_exec *exec)
{
	t_dic_entry	*entry;
	char	**arguments;
	char	*var;
	char	**env_keys;
	int		i;

	i = 0;
	arguments = (char **) exec->cmd->cmd->darray;
	if (arguments[1] == NULL)
	{
		env_keys = dict_get_keys(exec->env);
		sort_strings(env_keys, exec->env->capacity);
		while (env_keys[i])
			ft_printf("%s=%s\n", env_keys[i], dict_get(exec->env, env_keys[i]));
		return ;
	}
	while (arguments[i])
	{
		if (ft_strchr(arguments[i], '='))
			var = ft_strchr(arguments[i], '=') + 1;
		else
			var = NULL;
		if (is_valid_name(arguments[i]))
		{
			entry = dict_create_entry(arguments[i], var);
			dict_insert(&exec->env, entry);
		}
		else 
			export_error(arguments[i]);
		i++;
	}
}
/* 
	El codigo de abajo es para comprobar SI un name contiene assignment.

*/

// int
// assignment (
//      const char *string,
//      int flags
// )
// {
//   register unsigned char c;
//   register int newi, indx;

//   c = string[indx = 0];
//   if (legal_variable_starter (c) == 0)
//     return (0);

//   while (c = string[indx])
//     {
//       /* The following is safe.  Note that '=' at the start of a word
// 	 is not an assignment statement. */
//       if (c == '=')
// 	return (indx);

//       /* Check for `+=' */
//       if (c == '+' && string[indx+1] == '=')
// 	return (indx + 1);

//       /* Variable names in assignment statements may contain only letters,
// 	 digits, and `_'. */
//       if (legal_variable_char (c) == 0)
// 	return (0);

//       indx++;
//     }
//   return (0);
// }