/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 11:17:19 by pmilan            #+#    #+#             */
/*   Updated: 2018/06/05 23:15:39 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	i;
	size_t	j;
	size_t	length_s1;
	size_t	length_s2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	length_s1 = ft_strlen(s1);
	length_s2 = ft_strlen(s2);
	if (!(ret = (char *)malloc(length_s1 + length_s2 + 1)))
		return (NULL);
	while (i < length_s1)
	{
		ret[i] = s1[i];
		i++;
	}
	while (i < (length_s1 + length_s2))
		ret[i++] = s2[j++];
	ret[i] = 0;
	return (ret);
}
