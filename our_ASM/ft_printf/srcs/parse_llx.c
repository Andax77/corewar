/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_llx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 17:59:34 by eparisot          #+#    #+#             */
/*   Updated: 2018/02/15 15:27:24 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_parse_conv_llx(va_list ap, int *f_tab, long long *tmp)
{
	if (f_tab[7])
		*tmp = va_arg(ap, unsigned long);
	else if (f_tab[8])
		*tmp = va_arg(ap, unsigned long long);
	else if (f_tab[9])
	{
		*tmp = va_arg(ap, int);
		if (*tmp < 0)
			while (*tmp < 0)
				*tmp += 65536;
	}
	else if (f_tab[10])
	{
		*tmp = va_arg(ap, int);
		if (*tmp > 256)
			while (*tmp > 256)
				*tmp -= 256;
	}
	else if (f_tab[11])
		*tmp = va_arg(ap, uintmax_t);
	else if (f_tab[12])
		*tmp = va_arg(ap, size_t);
	else
		*tmp = va_arg(ap, unsigned int);
}

static void		ft_parse_4_llx(int *p_ret, int *f_tab)
{
	if ((f_tab[4] || f_tab[6] >= f_tab[5]) \
		&& !(f_tab[6] >= 0 && f_tab[6] < f_tab[5]))
		*p_ret += ft_putchar('0');
	else
		*p_ret += ft_putchar(' ');
	f_tab[5]--;
}

static void		ft_parse_1_llx(int *p_ret, int *f_tab, long long *tmp)
{
	if (f_tab[5] > f_tab[6])
		f_tab[5] = f_tab[5] - 2;
	if ((f_tab[6] > ft_countdigits_hex(*tmp) + 2 && *tmp) || (f_tab[6] != 0 \
			&& f_tab[4] && *tmp))
		ft_putstr("0X", p_ret);
	if (!f_tab[3])
		while (f_tab[5] > ft_countdigits_hex(*tmp))
			ft_parse_4_llx(p_ret, f_tab);
	if (f_tab[6] < ft_countdigits_hex(*tmp) + 2 && (!f_tab[4] || !f_tab[6]) && \
			*tmp)
		ft_putstr("0X", p_ret);
	if (f_tab[3] && *tmp == 0)
	{
		f_tab[5]++;
		f_tab[6]++;
	}
	if (f_tab[3] && f_tab[6] > ft_countdigits_hex(*tmp))
		while (f_tab[6]-- > ft_countdigits_hex(*tmp) && f_tab[5]--)
			*p_ret += ft_putchar('0');
	if (f_tab[6] != 0 || (f_tab[6] == 0 && *tmp > 0))
		ft_putnbr_hex_up_l(*tmp, p_ret);
	if (f_tab[3])
		while (f_tab[5]-- > ft_countdigits_hex(*tmp))
			*p_ret += ft_putchar(' ');
}

static void		ft_parse_3_llx(int *p_ret, int *f_tab, long long *tmp)
{
	if (*tmp == 0 && f_tab[6] == 0)
		f_tab[5]++;
	if (!f_tab[3])
		while (f_tab[5] > ft_countdigits_hex(*tmp))
		{
			if ((f_tab[4] || f_tab[6] >= f_tab[5]) \
				&& !(f_tab[6] >= 0 && f_tab[6] < f_tab[5]))
				*p_ret += ft_putchar('0');
			else
				*p_ret += ft_putchar(' ');
			f_tab[5]--;
		}
	if (f_tab[3] && f_tab[6] > ft_countdigits_hex(*tmp))
		while (f_tab[6]-- > ft_countdigits_hex(*tmp) && f_tab[5]--)
			*p_ret += ft_putchar('0');
	if (f_tab[6] != 0 || (f_tab[6] == 0 && *tmp > 0))
		ft_putnbr_hex_up_l(*tmp, p_ret);
	if (f_tab[3])
		while (f_tab[5]-- > ft_countdigits_hex(*tmp))
			*p_ret += ft_putchar(' ');
}

void			ft_parse_llx(va_list ap, int *p_ret, int *f_tab, long long tmp)
{
	ft_parse_conv_llx(ap, f_tab, &tmp);
	if ((tmp != 0 || f_tab[6] >= 0) && f_tab[0])
		ft_parse_1_llx(p_ret, f_tab, &tmp);
	else
		ft_parse_3_llx(p_ret, f_tab, &tmp);
}
