/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_w.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 19:47:34 by eparisot          #+#    #+#             */
/*   Updated: 2018/01/07 22:16:38 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putchar_w(const wchar_t wc)
{
	int		i;

	i = 0;
	if (wc <= 127)
		i += ft_putchar((char)wc);
	else if (wc <= 2047)
	{
		i += ft_putchar(192 | (wc >> 6 & 63));
		i += ft_putchar(49280 | (wc & 63));
	}
	else if (wc <= 65535)
	{
		i += ft_putchar(224 | (wc >> 12));
		i += ft_putchar(128 | (wc >> 6 & 63));
		i += ft_putchar(128 | (wc & 63));
	}
	else
	{
		i += ft_putchar(248 | (wc >> 18 & 63));
		i += ft_putchar(128 | (wc >> 12 & 63));
		i += ft_putchar(128 | (wc >> 6 & 63));
		i += ft_putchar(128 | (wc & 63));
	}
	return (i);
}
