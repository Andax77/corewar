/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 17:59:34 by eparisot          #+#    #+#             */
/*   Updated: 2018/01/16 03:17:32 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_parse_s_bis(va_list ap, int *p_ret, int *f_tab, char **tmp_s)
{
	*tmp_s = va_arg(ap, char *);
	if (!*tmp_s)
		*tmp_s = "(null)";
	if (f_tab[6] != -1 && (int)ft_strlen(*tmp_s) > f_tab[6] && !f_tab[3])
		f_tab[5] += (int)ft_strlen(*tmp_s) - f_tab[6];
	if (!f_tab[3] && *tmp_s)
		while (f_tab[5] > (int)ft_strlen(*tmp_s))
		{
			if (f_tab[4])
				*p_ret += ft_putchar('0');
			else
				*p_ret += ft_putchar(' ');
			f_tab[5]--;
		}
}

void		ft_parse_s(va_list ap, int *p_ret, int *f_tab, char *tmp_s)
{
	int tmp6;
	int tmp5;

	tmp6 = f_tab[6];
	tmp5 = f_tab[5];
	if (f_tab[7] || f_tab[8])
	{
		ft_parse_lls(ap, p_ret, f_tab, (wchar_t *)tmp_s);
		return ;
	}
	ft_parse_s_bis(ap, p_ret, f_tab, &tmp_s);
	if (f_tab[6] == -1 || f_tab[6] >= (int)ft_strlen(tmp_s))
		ft_putstr(tmp_s, p_ret);
	else
	{
		if (!tmp_s)
			tmp_s = "(null)";
		while (f_tab[6]--)
			*p_ret += ft_putchar(*tmp_s++);
	}
	if (f_tab[3] && tmp_s)
		while (tmp5-- >= tmp6 - f_tab[6] && tmp5 + 1 > (int)ft_strlen(tmp_s))
			*p_ret += ft_putchar(' ');
}
