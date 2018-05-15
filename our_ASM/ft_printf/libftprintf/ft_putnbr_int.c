/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 14:59:11 by eparisot          #+#    #+#             */
/*   Updated: 2017/12/20 21:18:17 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_int(int n, int *p_ret)
{
	long	trans;

	if (n > 2147483647 || n < -2147483648)
		return ;
	trans = n;
	if (n < 0)
	{
		*p_ret += ft_putchar('-');
		trans *= -1;
	}
	if (trans > 9)
	{
		ft_putnbr_int(trans / 10, p_ret);
		ft_putnbr_int(trans % 10, p_ret);
	}
	else
		*p_ret += ft_putchar(trans + '0');
}
