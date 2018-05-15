/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned_l.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 14:59:11 by eparisot          #+#    #+#             */
/*   Updated: 2017/12/30 23:59:30 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbr_unsigned_l(uintmax_t n, int *p_ret)
{
	if (n > 9)
	{
		ft_putnbr_unsigned_l(n / 10, p_ret);
		ft_putnbr_unsigned_l(n % 10, p_ret);
	}
	else
		*p_ret += ft_putchar(n + '0');
}
