#include "../tokenizer/tokenizer.h"
#include "../data_structs/dictionary.h"

int	is_quot_o_metach(char *str, int i)
{
	if (str[i] == '\"' || str[i] == '$' || str[i] == '\0')
		return (1);
	else
		return (0);
}

int	expand_dollar(char *str, char **expanded_str, int *i, t_dictionary *env)
{
	int		len_env_var;
	char	*tmp_expand_str;
	char	*env_var_name;
	char	*env_var_value;

	len_env_var = *i + 1;
	while (ft_isalnum(str[len_env_var]))
		len_env_var++;
	tmp_expand_str = *expanded_str;
	env_var_name = ft_substr(str, *i + 1, len_env_var - *i - 1);
	if (!env_var_name)
		return (free(tmp_expand_str), 0);
	env_var_value = dict_get(env, env_var_name);
	if (!env_var_value)
		env_var_value = "";
	*expanded_str = ft_strjoin(*expanded_str, env_var_value);
	if (!(*expanded_str))
		return (free(env_var_name), free(tmp_expand_str), 0);
	free(tmp_expand_str);
	free(env_var_name);
	*i = len_env_var - 1;
	return (1);
}

int	expand_normal_text(char *str, char **expanded_str, int *i)
{
	int		len_normal;
	char	*tmp_expand_str;
	char	*str_normal_text;

	len_normal = *i;
	while (str[len_normal] != '\'' && str[len_normal] != '\"' && str[len_normal] != '$' && str[len_normal] != '\0')
		len_normal++;
	tmp_expand_str = *expanded_str;
	str_normal_text = ft_substr(str, *i, len_normal - *i);
	if (!str_normal_text)
		return (free(tmp_expand_str), 0);
	*expanded_str = ft_strjoin(*expanded_str, str_normal_text);
	if (!(*expanded_str))
		return (free(str_normal_text), free(tmp_expand_str), 0);
	free(tmp_expand_str);
	free(str_normal_text);
	*i = len_normal - 1;
	return (1);
}

int	expand_simple_quote(char *str, char **expanded_str, int *i)
{
	int		len_quote;
	char	*tmp_expand_str;
	char	*str_quote;

	len_quote = *i;
	while (still_in_quote(str[len_quote], '\''))
		len_quote++;	
	tmp_expand_str = *expanded_str;
	str_quote = ft_substr(str, *i + 1, len_quote - *i - 2);
	if (!str_quote)
		return (free(tmp_expand_str), 0);
	*expanded_str = ft_strjoin(*expanded_str, str_quote);
	if (!(*expanded_str))
		return (free(str_quote), free(tmp_expand_str), 0);
	free(tmp_expand_str);
	free(str_quote);
	*i = len_quote - 1;
	return (1);
}

int	expand_double_quote(char *str, char **expanded_str, int *i, t_dictionary *env)
{
	int		len_quote;
	char	*tmp_expand_str;
	char	*str_quote;

	len_quote = *i;
	while (still_in_quote(str[len_quote], '\"'))
	{
		if (!is_quot_o_metach(str, len_quote) && !expand_normal_text(str, expanded_str, &len_quote))
			return (0);
		else if (str[len_quote] == '$')
		{
			*i = len_quote;
			if (!expand_dollar(str, expanded_str, i , env))
				return (0);
			len_quote = *i;
		}
		len_quote++;	
	}
	*i = len_quote - 1;
	return (1);
}

char	*expand_str(char *str, t_dictionary *env)
{
	int		i;
	int		normal_string;
	char	*expanded_str;

	i = 0;
	expanded_str = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '\'')
		{
			if (!expand_simple_quote(str, &expanded_str, &i))
				return (NULL);
		}
		else if (str[i] == '\"')
		{
			if (!expand_double_quote(str, &expanded_str, &i, env))
				return (NULL);
		}
		else if (str[i] == '$')
		{
			if (!expand_dollar(str, &expanded_str, &i, env))
				return (NULL);
		}
		else
		{
			if (!expand_normal_text(str, &expanded_str, &i))
				return (NULL);
		}
		i++;
	}
	return (expanded_str);
}

void	expand_tester();

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

	// char	*testeo = expand_str("\"PATH\"oo$'DISPLAY'", hash_env);
	// ft_printf("testeo: %s\n", testeo);
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

	ft_printf("%s: ", str);
	expanded_str = expand_str(str, env);
	ft_printf("\n\tmio: %s\n\techo: %s\n", expanded_str, expected);
	print_result(!ft_strncmp(expanded_str, expected, ft_strlen(expected)));
	free(expanded_str);
}

void	expand_tester(t_dictionary *env)
{
	char	*str;
	
	str = "$BAR\"ooo\"";
	make_test(str, env, "ooo");
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

	str = "\"PATH\r\"oo$'DISPLAY'";
	make_test(str, env, "PATH\rooDISPLAY");
	ft_printf("\n----------------------\n");

	str = "\"$LESS AAAAAAA $SHLVL\"";
	make_test(str, env, "-R AAAAAAA 1");
	ft_printf("\n----------------------\n");

	str = "\"$LESS A'AAAAAA $SHLVL\"";
	make_test(str, env, "-R A'AAAAAA 1");
	ft_printf("\n----------------------\n");

	str = "\"$LESS A'AAAAAA $SHLVL hola\"";
	make_test(str, env, "-R A'AAAAAA 1 hola");
	ft_printf("\n----------------------\n");
}
