/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex_p.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 14:59:11 by eparisot          #+#    #+#             */
/*   Updated: 2017/12/21 15:27:22 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_hex_p(uintmax_t n, int *p_ret)
{
	if (n > 15)
	{
		ft_putnbr_hex_p(n / 16, p_ret);
		ft_putnbr_hex_p(n % 16, p_ret);
	}
	else
	{
		if (n <= 9)
			*p_ret += ft_putchar(n + '0');
		else
			*p_ret += ft_putchar(n + 'a' - 10);
	}
}
