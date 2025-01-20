#include "tokenizer/tokenizer.h"

int	expand_dollar(char *str, char **expanded_str, int *i)
{

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
		// if (str[len_quote] == '$')
		// 	expand_dollar();
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

char	*expand_str(char *str)
{
	int		i;
	int		normal_string;
	char	*expanded_str;

	i = 0;
	while (str[i])
	{
		while (str[i] != '\'' && str[i] != '\"' && str[i] != '$' && str[i] != '\0')
			i++;
		expanded_str = ft_substr(str, 0, i); // Otra función que lo maneje.
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
		i++;
	}
	return (expanded_str);
}

int	main(void)
{
	char	*expanded_str = expand_str("DI\'Bar\'");
	ft_printf("%s\n", expanded_str);
	free(expanded_str);
	return (0);
}	