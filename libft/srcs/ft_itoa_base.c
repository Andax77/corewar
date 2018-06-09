/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 00:45:12 by eparisot          #+#    #+#             */
/*   Updated: 2018/06/09 16:47:12 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int		ft_count(long long value, int base)
{
	int		c;

	c = 1;
	if (value < 0 && base == 10)
		c++;
	while (value / base)
	{
		value /= base;
		c++;
	}
	return (c);
}

static char*	ft_itoa_base_bis(char *res, int c, long long nb, int base)
{
	while (nb >= base)
	{
		if (nb % base < 10)
			res[c] = (nb % base) + 48;
		else
			res[c] = (nb % base) - 10 + 97;
		nb /= base;
		c--;
	}
	if (nb < 10)
		res[c] = nb + 48;
	else
		res[c] = nb - 10 + 97;
	return (res);
}

char			*ft_itoa_base(long long value, int base)
{
	char		*res;
	int			c;
	long long	nb;

	res = NULL;
	if (base >= 2 && base <= 16)
	{
		res = NULL;
		c = ft_count(value, base);
		if ((res = (char *)malloc(c + 1)) == NULL)
			return (NULL);
		res[c--] = '\0';
		nb = value;
		if (value < 0)
		{
			if (base == 10)
				res[0] = '-';
			nb = -nb;
		}
		ft_itoa_base_bis(res, c, nb, base);
	}
	return (res);
}
