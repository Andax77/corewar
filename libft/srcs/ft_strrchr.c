/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strrchr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 12:33:20 by pmilan            #+#    #+#             */
/*   Updated: 2017/11/09 12:03:45 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strrchr(const char *str, int c)
{
	int		length;

	length = ft_strlen(str);
	while (length >= 0)
	{
		if (str[length] == c)
			return ((char *)str + length);
		length--;
	}
	return (0);
}
