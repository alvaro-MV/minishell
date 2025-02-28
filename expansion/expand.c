#include "../tokenizer/tokenizer.h"
#include "../data_structs/dictionary.h"

typedef enum expand_states
{
	WORD = 1,
	DOUBLE_QUOTE,
	SINGLE_QUOTE,
	ENV_VAR
}	expand_states;

char	*expand_str(char *str, t_dictionary *env)
{
	int				i;
	char			*expanded_str;
	char			*tmp_str;
	char			c[2];
	expand_states	state;
	expand_states	old_state;

	// Para la expansión de Variable
	int		len_env_var;
	char	*tmp_expand_str;
	char	*env_var_name;
	char	*env_var_value;

	i = 0;
	expanded_str = ft_strdup("");
	state = WORD;
	old_state = WORD;
	while (str[i])
	{
		if (state == WORD)
		{
			old_state = state;
			if (str[i] == '"')
				state = DOUBLE_QUOTE;
			else if (str[i] == '\'')
				state = SINGLE_QUOTE;
			else if ((str[i] == '$' && ft_isalnum(str[i + 1]))
					|| (str[i] == '$' && str[i + 1] == '\''))
				state = ENV_VAR;
			else
			{
				tmp_str = expanded_str;
				c[0] = str[i];
				c[1] = '\0';
				expanded_str = ft_strjoin(expanded_str, c);
				free(tmp_str);
			}
		}
		else if (state == DOUBLE_QUOTE)
		{
			if (old_state == ENV_VAR)
				i--;
			old_state = state;
			if (str[i] == '"')
				state = WORD;
			else if (str[i] == '$' && ft_isalnum(str[i + 1]))
				state = ENV_VAR;
			else
			{
				tmp_str = expanded_str;
				c[0] = str[i];
				c[1] = '\0';
				expanded_str = ft_strjoin(expanded_str, c);
				free(tmp_str);
			}
		}
		else if (state == SINGLE_QUOTE)
		{
			old_state = state;
			if (str[i] == '\'')
				state = WORD;
			else
			{
				tmp_str = expanded_str;
				c[0] = str[i];
				c[1] = '\0';
				expanded_str = ft_strjoin(expanded_str, c);
				free(tmp_str);
			}
		}
		else if (state == ENV_VAR)
		{
			state = old_state;
			old_state = ENV_VAR;
			len_env_var = i;
			if (str[i] == '\'')
			{
				// i--;				
				state = SINGLE_QUOTE;
			}
			else
			{
				while (ft_isalpha(str[len_env_var]))
					len_env_var++;
				tmp_str = expanded_str;
				env_var_name = ft_substr(str, i, len_env_var - i);
				if (!env_var_name)
					return (free(tmp_str), free(expanded_str), NULL);
				if (ft_strncmp(ft_strtrim(env_var_name, " \t\r"), " ", 2))
				{
					env_var_value = dict_get(env, env_var_name);
					if (!env_var_value)
						env_var_value = "";
				}
				expanded_str = ft_strjoin(expanded_str, env_var_value);
				free(tmp_str);
				free(env_var_name);
				i += len_env_var - 2;
				ft_printf("str i despues de expandir: %s\n", &str[i]);
			}
		}
		i++;
	}
	return (expanded_str);
}

void	expand_tester(t_dictionary *env);

int	main(int argc, char **argv, char **env)
{
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
	expand_tester(hash_env);
	dict_delete(hash_env);
	return (0);
}

void	print_result(int condition)
{
	if (!condition)
		ft_printf("\033[31m[KO]\033[0m");
	else
		ft_printf("\033[32m[OK]\033[0m");
}

void	make_test(char *str, t_dictionary *env, char *expected)
{
	char	*expanded_str;

	ft_printf("%s: \n", str);
	expanded_str = expand_str(str, env);
	ft_printf("\tm: %s\n\te: %s\n", expanded_str, expected);
	print_result(!ft_strncmp(expanded_str, expected, ft_strlen(expected)));
	free(expanded_str);
}

void	expand_tester(t_dictionary *env)
{
	char	*str;
	
	str = "$BAR\"ooo\"";
	make_test(str, env, "ooo");
	ft_printf("\n----------------------\n");

	str = "\"Hola\"a";
	make_test(str, env, "Holaa");
	ft_printf("\n----------------------\n");

	str = "\"$DISPLAY\"ooo\"i\"";
	make_test(str, env, ":0oooi");
	ft_printf("\n----------------------\n");

	str = "\"$DISPLA\"Yooo\"i\"";
	make_test(str, env, "Yoooi");
	ft_printf("\n----------------------\n");

	str = "\"$HOME\"/home/usuario";
	make_test(str, env, "/home/alvaro/home/usuario");
	ft_printf("\n----------------------\n");

	str = "'Cualquier mierda'";
	make_test(str, env, "Cualquier mierda");
	ft_printf("\n----------------------\n");

	str = "$DISPLAY'ooo\"i\"'";
	make_test(str, env, ":0ooo\"i\"");
	ft_printf("\n----------------------\n");

	str = "\"PATH\"oo$'DISPLAY'";
	make_test(str, env, "PATHooDISPLAY");
	ft_printf("\n----------------------\n");
	
	make_test("\"$?\"", env, "0");
	ft_printf("\n----------------------\n");

	make_test("\"$SHELL$\"", env, "/usr/bin/zsh$");
	ft_printf("\n----------------------\n");

	make_test("$SHELL$", env, "/usr/bin/zsh$");
	ft_printf("\n----------------------\n");

	make_test("\"$DISP\"'X'", env, "X");
	ft_printf("\n----------------------\n");

	make_test("$\"DISP\"'X'", env, "$DISPX");
	ft_printf("\n----------------------\n");
}
