/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 17:59:34 by eparisot          #+#    #+#             */
/*   Updated: 2018/01/09 14:37:39 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_parse_c(va_list ap, int *p_ret, int *f_tab)
{
	if (f_tab[7] || f_tab[8])
	{
		ft_parse_llc(ap, p_ret, f_tab);
		return ;
	}
	if (!f_tab[3])
		while (f_tab[5] > 1)
		{
			if (f_tab[4])
				*p_ret += ft_putchar('0');
			else
				*p_ret += ft_putchar(' ');
			f_tab[5]--;
		}
	*p_ret += ft_putchar(va_arg(ap, int));
	if (f_tab[3])
		while (f_tab[5] > 1)
		{
			*p_ret += ft_putchar(' ');
			f_tab[5]--;
		}
}

void			ft_parse_llc(va_list ap, int *p_ret, int *f_tab)
{
	if (!f_tab[3])
		while (f_tab[5] > 1)
		{
			if (f_tab[4])
				*p_ret += ft_putchar('0');
			else
				*p_ret += ft_putchar(' ');
			f_tab[5]--;
		}
	*p_ret += ft_putchar_w(va_arg(ap, wchar_t));
	if (f_tab[3])
		while (f_tab[5] > 1)
		{
			*p_ret += ft_putchar(' ');
			f_tab[5]--;
		}
}
