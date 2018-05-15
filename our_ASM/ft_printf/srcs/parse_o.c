/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_o.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 17:59:34 by eparisot          #+#    #+#             */
/*   Updated: 2018/02/14 17:39:21 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_parse_conv_o(va_list ap, int *f_tab, long long *tmp)
{
	if (f_tab[7])
		*tmp = va_arg(ap, unsigned long);
	else if (f_tab[8])
		*tmp = va_arg(ap, unsigned long long);
	else if (f_tab[9])
	{
		if ((*tmp = va_arg(ap, int)) < 0)
			while (*tmp < 0)
				*tmp += 65536;
	}
	else if (f_tab[10])
	{
		if ((*tmp = va_arg(ap, int)) > 256)
			while (*tmp > 256)
				*tmp -= 256;
		else if (*tmp < 0)
			while (*tmp < 0)
				*tmp += 256;
	}
	else if (f_tab[11])
		*tmp = va_arg(ap, uintmax_t);
	else if (f_tab[12])
		*tmp = va_arg(ap, size_t);
	else
		*tmp = va_arg(ap, unsigned int);
}

static void		ft_parse_3_o(int *p_ret, int *f_tab)
{
	if ((f_tab[4] || f_tab[6] >= f_tab[5]) \
		&& !(f_tab[6] >= 0 && f_tab[6] < f_tab[5]))
		*p_ret += ft_putchar('0');
	else
		*p_ret += ft_putchar(' ');
	f_tab[5]--;
}

static void		ft_parse_1_o(int *p_ret, int *f_tab, long long *tmp)
{
	if (*tmp != 0)
		f_tab[5]--;
	if ((f_tab[6] > ft_countdigits_oct(*tmp) && *tmp) || (f_tab[6] != 0 \
		&& f_tab[4] && *tmp))
		*p_ret += ft_putchar('0');
	if (!f_tab[3])
		while (f_tab[5] > ft_countdigits_oct(*tmp))
			ft_parse_3_o(p_ret, f_tab);
	if (f_tab[6] < ft_countdigits_oct(*tmp) && (!f_tab[4] || !f_tab[6]))
		*p_ret += ft_putchar('0');
	if (f_tab[3] && *tmp == 0)
	{
		f_tab[6]++;
		f_tab[5]++;
	}
	if (f_tab[3] && f_tab[6] > ft_countdigits_oct(*tmp))
		while (f_tab[6]-- > ft_countdigits_oct(*tmp) && f_tab[5]--)
			*p_ret += ft_putchar('0');
	if (f_tab[6] != 0 || (f_tab[6] == 0 && *tmp > 0))
		ft_putnbr_oct_l(*tmp, p_ret);
	if (f_tab[3])
		while (--f_tab[5] >= ft_countdigits_oct(*tmp))
			*p_ret += ft_putchar(' ');
}

static void		ft_parse_2_o(int *p_ret, int *f_tab, long long *tmp)
{
	if (*tmp == 0 && f_tab[6] == 0)
		f_tab[5]++;
	if (!f_tab[3])
		while (f_tab[5] > ft_countdigits_oct(*tmp))
		{
			if ((f_tab[4] || f_tab[6] >= f_tab[5]) \
				&& !(f_tab[6] >= 0 && f_tab[6] < f_tab[5]))
				*p_ret += ft_putchar('0');
			else
				*p_ret += ft_putchar(' ');
			f_tab[5]--;
		}
	if (f_tab[3] && f_tab[6] > ft_countdigits_oct(*tmp))
		while (f_tab[6]-- > ft_countdigits_oct(*tmp) && f_tab[5]--)
			*p_ret += ft_putchar('0');
	if (f_tab[6] != 0 || (f_tab[6] == 0 && *tmp > 0))
		ft_putnbr_oct_l(*tmp, p_ret);
	if (f_tab[3])
		while (f_tab[5]-- > ft_countdigits_oct(*tmp))
			*p_ret += ft_putchar(' ');
}

void			ft_parse_o(va_list ap, int *p_ret, int *f_tab, long long tmp)
{
	ft_parse_conv_o(ap, f_tab, &tmp);
	if ((tmp != 0 || f_tab[6] >= 0) && f_tab[0])
		ft_parse_1_o(p_ret, f_tab, &tmp);
	else
		ft_parse_2_o(p_ret, f_tab, &tmp);
}
