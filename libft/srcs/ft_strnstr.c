/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 12:39:02 by pmilan            #+#    #+#             */
/*   Updated: 2017/11/10 15:32:40 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strnstr(const char *str, const char *to_find, size_t size)
{
	size_t i;
	size_t y;

	if (to_find[0] == 0)
		return ((char *)str);
	i = 0;
	while (str[i] && i < size)
	{
		y = 0;
		while ((str[i + y] == to_find[y]) && ((i + y) < size))
		{
			if (to_find[y + 1] == '\0')
				return (&((char *)str)[i]);
			y++;
		}
		i++;
	}
	return (0);
}
