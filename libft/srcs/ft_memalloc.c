/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 17:03:32 by pmilan            #+#    #+#             */
/*   Updated: 2017/11/08 19:09:51 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

void	*ft_memalloc(size_t size)
{
	void *ret;

	if (!(ret = (void*)malloc(size)))
		return (NULL);
	ft_bzero(ret, size);
	return (ret);
}
