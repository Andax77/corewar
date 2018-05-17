/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_to_nbase.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 13:57:17 by pmilan            #+#    #+#             */
/*   Updated: 2018/01/04 13:57:25 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>

char		*ft_int_to_nbase(long n, char *base, int size)
{
	char			*ret;
	unsigned long	un;

	un = (n < 0) ? (unsigned long)-n : (unsigned long)n;
	if (!(ret = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ret[size] = '\0';
	while (size > 0)
	{
		ret[--size] = base[un % ft_strlen(base)];
		un /= ft_strlen(base);
	}
	if (n < 0)
		ret[0] = '1';
	return (ret);
}
