/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:10:38 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/16 18:13:12 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYNAMIC_ARRAY_H
# define DYNAMIC_ARRAY_H

# include "../libft/include/get_next_line.h"
# include "../libft/include/libft.h"
# include <stdlib.h>
# include <unistd.h>

typedef struct s_darray
{
	void		*darray;
	size_t		len;
	size_t		full_idx;
	size_t		size;
}				t_darray;

t_darray		*alloc_darray(size_t len, size_t size);
int				resize_darray(t_darray **darray);
void			free_darray(t_darray *darray);
int				append_darray(t_darray **darray, void *element);
unsigned char	*r_darray(t_darray *darray, int idx);

#endif