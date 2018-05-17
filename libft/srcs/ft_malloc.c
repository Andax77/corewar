/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 19:17:29 by pmilan            #+#    #+#             */
/*   Updated: 2018/02/02 19:17:55 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>

void	*ft_malloc(size_t len, int exit_value)
{
	void *ptr;

	if (!(ptr = malloc(len)))
		exit(exit_value);
	ft_bzero(ptr, len);
	return (ptr);
}
