/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 10:50:58 by pmilan            #+#    #+#             */
/*   Updated: 2017/11/10 17:12:00 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t			ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t i;
	size_t length_d;
	size_t length_s;

	i = 0;
	length_d = ft_strlen(dest);
	length_s = ft_strlen((char *)src);
	if (size <= length_d)
		return (size + length_s);
	if (size == length_d + 1)
		return (size + length_s - 1);
	while (src[i] != '\0' && i < size - length_d - 1)
	{
		dest[i + length_d] = src[i];
		i++;
	}
	dest[i + length_d] = '\0';
	return (length_d + length_s);
}
