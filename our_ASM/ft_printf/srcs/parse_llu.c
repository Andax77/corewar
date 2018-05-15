/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_llu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 17:59:34 by eparisot          #+#    #+#             */
/*   Updated: 2018/01/24 00:18:23 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_parse_conv_llu(va_list ap, int *f_tab, long long *tmp)
{
	if (f_tab[7])
		*tmp = va_arg(ap, unsigned long);
	else if (f_tab[8])
		*tmp = va_arg(ap, unsigned long long);
	else if (f_tab[10])
	{
		*tmp = va_arg(ap, int);
		if (*tmp > 65535)
			while (*tmp > 65535)
				*tmp -= 65535;
	}
	else if (f_tab[11])
		*tmp = va_arg(ap, uintmax_t);
	else if (f_tab[12])
		*tmp = va_arg(ap, size_t);
	else
		*tmp = va_arg(ap, unsigned long);
}

void			ft_parse_llu(va_list ap, int *p_ret, int *f_tab, long long tmp)
{
	ft_parse_conv_llu(ap, f_tab, &tmp);
	if (!f_tab[3])
		while (f_tab[5] - ft_countdigits_u(tmp) > 0)
		{
			if ((f_tab[4] || f_tab[6] >= f_tab[5]) \
			&& !(f_tab[6] >= 0 && f_tab[6] < f_tab[5]))
				*p_ret += ft_putchar('0');
			else
				*p_ret += ft_putchar(' ');
			f_tab[5]--;
		}
	else if (f_tab[3] && f_tab[6] > ft_countdigits_u(tmp))
		while (f_tab[6]-- > ft_countdigits_u(tmp) && f_tab[5]--)
			*p_ret += ft_putchar('0');
	if (f_tab[6] != 0 || (f_tab[6] == 0 && tmp > 0))
		ft_putnbr_unsigned_l(tmp, p_ret);
	if (f_tab[3])
		while (f_tab[5] - ft_countdigits_u(tmp) > 0)
		{
			*p_ret += ft_putchar(' ');
			f_tab[5]--;
		}
}
