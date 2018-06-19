/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 10:41:45 by pmilan            #+#    #+#             */
/*   Updated: 2017/11/09 13:52:43 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strncat(char *dest, const char *src, size_t nb)
{
	size_t i;
	size_t j;
	size_t length_dest;

	j = 0;
	length_dest = ft_strlen(dest);
	i = length_dest;
	while (i < length_dest + nb && src[j] != '\0')
		dest[i++] = src[j++];
	dest[i] = '\0';
	return (dest);
}
