/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lld.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 17:59:34 by eparisot          #+#    #+#             */
/*   Updated: 2018/01/23 23:01:51 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_parse_conv_lld(va_list ap, int *f_tab, long long *tmp)
{
	if (f_tab[7])
		*tmp = va_arg(ap, long);
	else if (f_tab[8])
		*tmp = va_arg(ap, long long);
	else if (f_tab[10])
	{
		*tmp = va_arg(ap, int);
		if (*tmp > 65535)
			while (*tmp > 65535)
				*tmp -= 65535;
	}
	else if (f_tab[11])
		*tmp = va_arg(ap, intmax_t);
	else if (f_tab[12])
		*tmp = va_arg(ap, size_t);
	else
		*tmp = va_arg(ap, long);
}

static void		ft_parse_1_lld(va_list ap, int *p_rt, int *f_tb, long long *tmp)
{
	ft_parse_conv_lld(ap, f_tb, tmp);
	if (f_tb[5] <= ft_countdigits(*tmp) || (f_tb[6] > -1 && \
	f_tb[6] <= ft_countdigits(*tmp)) || f_tb[4])
	{
		if (*tmp >= 0)
		{
			if (f_tb[2] && f_tb[4] == 0)
			{
				*p_rt += ft_putchar('+');
				f_tb[5]--;
				f_tb[2] = 0;
			}
		}
		else
			f_tb[2] = 0;
	}
	if (f_tb[1] && *tmp >= 0)
	{
		*p_rt += ft_putchar(' ');
		if (f_tb[5] > f_tb[6])
			f_tb[5]--;
	}
}

static void		ft_parse_3_lld(int *p_ret, int *f_tab, long long *tmp)
{
	if ((f_tab[4] || f_tab[6] >= f_tab[5]) && \
			!(f_tab[6] >= 0 && f_tab[6] < f_tab[5]))
	{
		if (tmp < 0)
		{
			*p_ret += ft_putchar('-');
			if (f_tab[6] > f_tab[5] || (f_tab[6] == -1 && f_tab[4]))
				f_tab[5]--;
			*tmp *= -1;
		}
		else if (f_tab[2] && *tmp >= 0)
		{
			*p_ret += ft_putchar('+');
			f_tab[2] = 0;
		}
		*p_ret += ft_putchar('0');
	}
	else
		*p_ret += ft_putchar(' ');
	f_tab[5]--;
}

static void		ft_parse_2_lld(int *p_ret, int *f_tab, long long *tmp)
{
	while (f_tab[5] > ft_countdigits(*tmp))
	{
		if (f_tab[6] >= 0 && f_tab[6] < f_tab[5])
			if (tmp < 0 && (f_tab[5] - f_tab[6]) == 1)
			{
				*p_ret += ft_putchar('-');
				f_tab[5]--;
				*tmp *= -1;
			}
		ft_parse_3_lld(p_ret, f_tab, tmp);
	}
}

void			ft_parse_lld(va_list ap, int *p_ret, int *f_tab, long long tmp)
{
	ft_parse_1_lld(ap, p_ret, f_tab, &tmp);
	if (tmp >= 0 && f_tab[2] && !f_tab[3])
		f_tab[5]--;
	if (!(f_tab[6] != 0 || (f_tab[6] == 0 && tmp != 0)))
		f_tab[5] += ft_countdigits(tmp);
	if (!f_tab[3])
		ft_parse_2_lld(p_ret, f_tab, &tmp);
	if (f_tab[2] && tmp >= 0)
	{
		*p_ret += ft_putchar('+');
		f_tab[2] = 0;
		f_tab[5]--;
	}
	if (f_tab[3] && f_tab[6] > ft_countdigits(tmp))
		while (f_tab[6]-- > ft_countdigits(tmp) && f_tab[5]--)
			*p_ret += ft_putchar('0');
	if (f_tab[6] != 0 || (f_tab[6] == 0 && tmp != 0))
		ft_putnbr(tmp, p_ret);
	if (f_tab[3])
		while (f_tab[5] - ft_countdigits(tmp) > 0)
		{
			*p_ret += ft_putchar(' ');
			f_tab[5]--;
		}
}
