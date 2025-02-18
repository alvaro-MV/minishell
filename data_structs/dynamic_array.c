#include "dynamic_array.h"
#include <stdio.h>
#include "../tokenizer/tokenizer.h" //testeo

void	free_darray(t_darray *darray);

t_darray	*alloc_darray(size_t len, size_t size)
{
	t_darray	*ret_darray;
	
	ret_darray = (t_darray *) ft_calloc(1, sizeof(t_darray));
	if (!ret_darray)
		return (NULL);
	ret_darray->darray = ft_calloc(len, sizeof(size));
	if (!ret_darray->darray)
		return (free(ret_darray), NULL);
	ret_darray->len = len;
	ret_darray->size = size;
	ret_darray->full_idx = 0;
	return (ret_darray);
}

int	resize_darray(t_darray **darray)
{
	size_t			i;
	void			*resz_darray;
	unsigned char	*str_darray;
	unsigned char	*str_resz_darray;

	i = 0;
	str_darray = (unsigned char *) (*darray)->darray;
	resz_darray = ft_calloc((2 * (*darray)->len), (*darray)->size);
	if (!resz_darray)
		return (0);
	str_resz_darray = (unsigned char *) resz_darray;
	while (i < (*darray)->len * (*darray)->size)
	{
		str_resz_darray[i] = str_darray[i];
		i++;
	}
	(*darray)->len *= 2;
	free((*darray)->darray);
	(*darray)->darray = resz_darray;
	return (1);
}

void	free_darray(t_darray *darray)
{
	free(darray->darray);
	free(darray);
}

unsigned char	*r_darray(t_darray *darray, int idx)
{
	unsigned char	*str_darr;
	int				full_idx;
	size_t			bytes_size;

	full_idx = (int) darray->full_idx;
	if (-idx > full_idx || idx > full_idx - 1)
		return (NULL);
	if (idx >= 0)
		bytes_size = idx * darray->size;
	else
		bytes_size = (size_t) (full_idx + idx) * darray->size;
	str_darr = &((unsigned char *) darray->darray)[bytes_size];
	return (str_darr);
}

int	append_darray(t_darray **darray, void *element)
{
	unsigned char	*str_darray;
	unsigned char	*str_element;
	size_t			i;

	i = 0;
	if ((*darray)->full_idx == (*darray)->len)
	{
		if (!resize_darray(darray))
			return (free_darray(*darray), 0);
	}
	if ((*darray)->full_idx)
		str_darray = (unsigned char *) r_darray(*darray, -1);
	else
		str_darray = (unsigned char *) (*darray)->darray;
	str_element = (unsigned char *) element;
	printf("ptr de darray a la hora de introducir: %p\n", str_darray); //testeo
	while (i < (*darray)->size)
	{
		// str_darray[((*darray)->full_idx * (*darray)->size) + i] = str_element[i];
		str_darray[i] = str_element[i];
		i++;
	}
	(*darray)->full_idx++;
	return (1);
}

int	main(void)
{
	t_token	t_entry;
	t_darray	*darr = alloc_darray(4, sizeof(t_token));

	if (!darr)
		return (printf("Hijos de putaaaaaaaaa\n"));
	
	int i = 0;
	while (i < 5)
	{
		t_entry.text = ft_itoa(i);
		t_entry.type = -1;
		if (!append_darray(&darr, &t_entry))
			return (1);
		i++;
	}
	for (int j = 0; j < darr->full_idx; j++)
		printf("j: %d  darr: %s\n", j, ((t_token *)(darr->darray))[j].text);
	free_darray(darr);
}
