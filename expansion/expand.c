#include "../tokenizer/tokenizer.h"
#include "../data_structs/dictionary.h"

int	expand_dollar(char *str, char **expanded_str, int *i, t_dictionary *env)
{
	int		len_env_var;
	char	*tmp_expand_str;
	char	*env_var_name;
	char	*env_var_value;

	len_env_var = *i + 1;
	while (str[len_env_var] != '\'' && str[len_env_var] != '\"'
			 && str[len_env_var] != '$' && str[len_env_var] != '\0')
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
		if (str[len_quote] == '$')
			expand_dollar(str, expanded_str, i, env);
		len_quote++;	
	}
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

int	expand_normal_text(char *str, char **expanded_str, int *i)
{
	int		len_normal;
	char	*tmp_expand_str;
	char	*str_normal_text;

	len_normal = *i;
	while (str[len_normal] != '\'' && str[len_normal] != '\"' && str[len_normal] != '$' && str[len_normal] != '\0')
		len_normal++;	
	tmp_expand_str = *expanded_str;
	str_normal_text = ft_substr(str, *i, len_normal);
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

	str = str;
	ft_printf("%s: ", str);
	expanded_str = expand_str(str, env);
	print_result(ft_strncmp(expanded_str, expected, ft_strlen(expected)));
	free(expanded_str);
}

void	expand_tester(t_dictionary *env)
{
	char	*str;
	
	str = "$BAR\"ooo\"";
	make_test(str, env, "\"ooo\"");
	ft_printf("\n----------------------\n");

	str = "\"$DISPLAY\"ooo\"i\"";
	make_test(str, env, "\":0\"ooo\"i\"");
	ft_printf("\n----------------------\n");

	str = "\"$DISPLA\"Yooo\"i\"";
	make_test(str, env, "Yoooi");
	ft_printf("\n----------------------\n");

	str = "\"$HOME\"/home/usuario";
	make_test(str, env, "/home/alvaro/home/usuario");
	ft_printf("\n----------------------\n");

	str = "'Cualquier mierda'";
	make_test(str, env, "'Cualquier mierda'");
	ft_printf("\n----------------------\n");

	str = "$DISPLAY'ooo\"i\"'";
	make_test(str, env, "'Cualquier mierda'");
	ft_printf("\n----------------------\n");
}
