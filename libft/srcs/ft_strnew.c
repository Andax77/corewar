/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 17:18:52 by pmilan            #+#    #+#             */
/*   Updated: 2017/11/10 19:25:39 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

char	*ft_strnew(size_t size)
{
	char *new;

	if (!(new = (char *)malloc(sizeof(*new) * (size + 1))))
		return (NULL);
	ft_bzero(new, size + 1);
	return (new);
}
