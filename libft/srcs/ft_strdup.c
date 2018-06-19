/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:51:47 by pmilan            #+#    #+#             */
/*   Updated: 2018/01/29 19:52:06 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

char	*ft_strdup(const char *src)
{
	int		length;
	int		i;
	char	*copy;

	i = 0;
	length = ft_strlen(src);
	if (!(copy = (char*)malloc(sizeof(*copy) * (length + 1))))
		return (NULL);
	copy[length] = '\0';
	while (src[i])
	{
		copy[i] = src[i];
		i++;
	}
	return (copy);
}
