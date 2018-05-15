/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 14:59:11 by eparisot          #+#    #+#             */
/*   Updated: 2017/12/22 17:44:17 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(long n, int *p_ret)
{
	unsigned long long trans;

	trans = n;
	if (n < 0)
	{
		*p_ret += ft_putchar('-');
		trans *= -1;
	}
	if (trans > 9)
	{
		ft_putnbr(trans / 10, p_ret);
		ft_putnbr(trans % 10, p_ret);
	}
	else
		*p_ret += ft_putchar(trans + '0');
}
