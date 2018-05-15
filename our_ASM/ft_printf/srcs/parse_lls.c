/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 17:59:34 by eparisot          #+#    #+#             */
/*   Updated: 2018/01/16 03:22:16 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_count_b(wchar_t *tmp_ws, int n)
{
	int		count;
	int		tmp;
	int		i;

	i = 0;
	tmp = 0;
	count = 0;
	while (n)
	{
		tmp += ft_wcharlen(tmp_ws[i]);
		if (tmp <= n)
			count += tmp;
		n--;
		i++;
	}
	return (count);
}

static void	ft_parse_lls_b(va_list ap, int *p_ret, int *f_tab, wchar_t **tmp_ws)
{
	*tmp_ws = va_arg(ap, wchar_t *);
	if (f_tab[6] != -1 && (int)ft_strlen_w(*tmp_ws) > f_tab[6])
		f_tab[5] += (int)ft_strlen_w(*tmp_ws) - ft_count_b(*tmp_ws, f_tab[6]);
	if (!f_tab[3] && *tmp_ws)
		while (f_tab[5] > (int)ft_strlen_w(*tmp_ws))
		{
			if (f_tab[4])
				*p_ret += ft_putchar('0');
			else
				*p_ret += ft_putchar(' ');
			f_tab[5]--;
		}
}

void		ft_parse_lls(va_list ap, int *p_ret, int *f_tab, wchar_t *tmp_ws)
{
	int tmp_ret;
	int tmp6;
	int tmp5;

	tmp_ret = 0;
	tmp6 = f_tab[6];
	tmp5 = f_tab[5];
	ft_parse_lls_b(ap, p_ret, f_tab, &tmp_ws);
	if (f_tab[6] == -1 || f_tab[6] >= (int)ft_strlen_w(tmp_ws))
		ft_putstr_w(tmp_ws, p_ret);
	else
	{
		if (!tmp_ws)
			tmp_ws = L"(null)";
		while (f_tab[6] >= (int)ft_wcharlen(tmp_ws[0]))
		{
			tmp_ret = ft_putchar_w(*tmp_ws++);
			f_tab[6] -= tmp_ret;
			*p_ret += tmp_ret;
		}
	}
	if (f_tab[3] && tmp_ws)
		while (tmp5-- >= tmp6 - f_tab[6] && tmp5 + 1 > (int)ft_strlen_w(tmp_ws))
			*p_ret += ft_putchar(' ');
}
