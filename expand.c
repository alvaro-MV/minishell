#include "tokenizer/tokenizer.h"
#include "data_structs/dictionary.h"

int	expand_dollar(char *str, char **expanded_str, int *i)
{
	int		len_env_var;
	char	*tmp_expand_str;
	char	*str_env_var;

	len_env_var = *i + 1;
	while (str[len_env_var] != '\'' && str[len_env_var] != '\"'
			 && str[len_env_var] != '$' && str[len_env_var] != '\0')
		len_env_var++;
	tmp_expand_str = *expanded_str;
	// str_env_var = ft_substr(str, *i + 1, len_env_var - *i - 1);
	// if (!str_env_var)
	// 	return (free(tmp_expand_str), 0);
	// ft_printf("str_env_var: %s\n", str_env_var);
	str_env_var = ft_strdup("");
	*expanded_str = ft_strjoin(*expanded_str, str_env_var);
	// *expanded_str = ft_strjoin(*expanded_str, str_env_var);
	// if (!(*expanded_str))
	// 	return (free(str_env_var), free(tmp_expand_str), 0);
	free(tmp_expand_str);
	free(str_env_var);
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

int	expand_double_quote(char *str, char **expanded_str, int *i)
{
	int		len_quote;
	char	*tmp_expand_str;
	char	*str_quote;

	len_quote = *i;
	while (still_in_quote(str[len_quote], '\"'))
	{
		if (str[len_quote] == '$')
			expand_dollar(str, expanded_str, i);
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
			if (!expand_double_quote(str, &expanded_str, &i))
				return (NULL);
		}
		else if (str[i] == '$')
		{
			if (!expand_dollar(str, &expanded_str, &i))
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

int	main(int argc, char **argv, char **env)
{
	char	*expanded_str = expand_str("DI$Bar\"\'Hola\"peste");
	ft_printf("expanded_str: %s\n", expanded_str);
	ft_printf("%d\n", ft_strcmp(expanded_str, "DI\'Holapeste"));
	free(expanded_str);
	expanded_str = expand_str("DI\'$Bar\'\"\'Hola\"peste");
	ft_printf("%d\n", ft_strcmp(expanded_str, "DI$Bar\'Holapeste"));
	free(expanded_str);
	return (0);
}	