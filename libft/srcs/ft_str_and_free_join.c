/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_and_free_join.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 17:30:14 by pmilan            #+#    #+#             */
/*   Updated: 2018/05/17 17:36:39 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

char		*ft_str_and_free_join(char *s1, const char *s2)
{
	char	*ret;
	int		i;
	int		lens1;
	int		lens2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	if (!(ret = (char *)malloc(sizeof(*ret) * (lens1 + lens2 + 1))))
		return (NULL);
	i = -1;
	while (++i < lens1)
		ret[i] = s1[i];
	i--;
	while (++i < lens1 + lens2)
		ret[i] = s2[i - lens1];
	ret[i] = '\0';
	free(s1);
	return (ret);
}
