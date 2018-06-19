/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 10:59:51 by pmilan            #+#    #+#             */
/*   Updated: 2017/11/12 15:17:11 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*ret;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	if (!(ret = (char *)malloc(sizeof(*ret) * (len + 1))))
		return (NULL);
	while (len > 0)
	{
		ret[i] = s[start];
		i++;
		start++;
		len--;
	}
	ret[i] = 0;
	return (ret);
}
