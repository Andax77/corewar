/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 18:35:12 by pmilan            #+#    #+#             */
/*   Updated: 2017/11/10 12:25:21 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int		ft_count_ch(int nb)
{
	int				nb_ch;
	unsigned int	nb2;

	nb_ch = 1;
	if (nb < 0)
		nb_ch++;
	nb2 = (nb < 0) ? (unsigned int)-nb : (unsigned int)nb;
	while (nb2 > 9)
	{
		nb_ch++;
		nb2 /= 10;
	}
	return (nb_ch);
}

char			*ft_itoa(int n)
{
	int				nb_ch;
	unsigned int	n2;
	char			*ret;

	nb_ch = ft_count_ch(n);
	n2 = (n < 0) ? (unsigned int)-n : (unsigned int)n;
	if (!(ret = (char*)malloc(sizeof(*ret) * (nb_ch + 1))))
		return (NULL);
	ret[nb_ch] = 0;
	nb_ch--;
	if (n < 0)
		ret[0] = '-';
	while (n2 > 0)
	{
		ret[nb_ch] = '0' + (n2 % 10);
		n2 /= 10;
		nb_ch--;
	}
	if (n == 0)
		ret[0] = '0';
	return (ret);
}
