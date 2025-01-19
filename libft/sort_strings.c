#include "include/libft.h"

void	sort_strings(char **strings, int n)
{
	char	*temp;
	int 	i;
	int 	j;

	i = 0;
	j = 0;
	while (i < n - 1)
	{
		while (j < n)
		{
			if (ft_strcmp(strings[i], strings[j]) > 0)
			{
				temp = strings[i];
				strings[i] = strings[j];
				strings[j] = temp;
			}
			j++;
		}
		i++;
	}
}
