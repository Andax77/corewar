/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 15:57:02 by pmilan            #+#    #+#             */
/*   Updated: 2017/12/18 15:57:19 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

char		*ft_strndup(const char *s1, int n)
{
	char	*ret;
	int		i;

	if (!(ret = (char*)malloc(sizeof(*ret) * (n + 1))))
		return (NULL);
	i = -1;
	while (++i < n)
		ret[i] = s1[i];
	ret[i] = '\0';
	return (ret);
}
