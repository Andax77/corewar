/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 17:59:34 by eparisot          #+#    #+#             */
/*   Updated: 2018/01/24 01:25:58 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_parse_p(va_list ap, int *p_ret, int *f_tab, long long tmp)
{
	tmp = va_arg(ap, uintmax_t);
	if (f_tab[6] >= f_tab[5])
	{
		f_tab[4] = 1;
		f_tab[5] += 2;
	}
	f_tab[4] ? ft_putstr("0x", p_ret) : 0;
	if (!f_tab[3])
		while (f_tab[5] - 2 - ft_countdigits_hex(tmp) > 0)
		{
			if (f_tab[4])
				*p_ret += ft_putchar('0');
			else
				*p_ret += ft_putchar(' ');
			f_tab[5]--;
		}
	!f_tab[4] ? ft_putstr("0x", p_ret) : 0;
	if (f_tab[6] != 0 || (f_tab[6] == 0 && tmp > 0))
		ft_putnbr_hex_p(tmp, p_ret);
	if (f_tab[3])
		while (f_tab[5] - 2 - ft_countdigits_hex(tmp) > 0)
		{
			*p_ret += ft_putchar(' ');
			f_tab[5]--;
		}
}
