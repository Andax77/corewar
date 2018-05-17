/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 18:46:56 by pmilan            #+#    #+#             */
/*   Updated: 2017/11/12 15:13:47 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*ret;
	int		i;

	if (s == NULL)
		return (NULL);
	i = 0;
	if (!(ret = (char *)malloc(sizeof(*ret) * ((ft_strlen((char *)(s))) + 1))))
		return (NULL);
	while (s[i])
	{
		ret[i] = f(s[i]);
		i++;
	}
	ret[i] = 0;
	return (ret);
}
