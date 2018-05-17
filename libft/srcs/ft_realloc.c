/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 13:55:22 by pmilan            #+#    #+#             */
/*   Updated: 2018/01/04 13:55:26 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

void		*ft_realloc(void *ptr, size_t original_size, size_t new_size)
{
	void	*new;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	else if (ptr == NULL)
		return (malloc(new_size));
	if ((new = malloc(new_size)) == NULL)
		return (NULL);
	if (new_size < original_size)
		ft_memcpy(new, ptr, new_size);
	else
		ft_memcpy(new, ptr, original_size);
	free(ptr);
	return (new);
}
