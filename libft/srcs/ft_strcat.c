/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 10:20:49 by pmilan            #+#    #+#             */
/*   Updated: 2017/11/09 11:49:01 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strcat(char *dest, const char *src)
{
	int i;
	int j;
	int length_dest;
	int length_src;

	j = 0;
	length_dest = ft_strlen(dest);
	length_src = ft_strlen(src);
	i = length_dest;
	while (i < length_dest + length_src)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
