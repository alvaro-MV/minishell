#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "libft/include/libft.h"

#define MAX 100


void	sortStrings(char **strings, int n)
{
	char	*temp;

	int i, j;
	for (i = 0; i < n - 1; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			if (ft_strcmp(strings[i], strings[j]) > 0)
			{
				temp = strings[i];
				strings[i] = strings[j];
				strings[j] = temp;
			}
		}
	}
}

int	main(void)
{
	char	*names[] = {"Florida", "Oregon", "California", "Georgia"};
	int		n;

	n = sizeof(names) / sizeof(names[0]);
	printf("Original size: %d\n", n);
	sortStrings(names, n);
	printf("\nSorted array:\n");
	for (int i = 0; i < n; i++)
	{
		printf("%s\n", names[i]);
	}
	return (0);
}
