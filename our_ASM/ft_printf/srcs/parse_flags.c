/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 17:59:34 by eparisot          #+#    #+#             */
/*   Updated: 2018/01/23 22:53:04 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_parse_f_flags_simples(char **types, int i, int j, int *f_tab)
{
	if (types[j][i] == '#')
		f_tab[0] = ++i;
	if (types[j][i] == '+')
		f_tab[2] = ++i;
	while (types[j][i] == ' ')
		f_tab[1] = ++i;
	if (types[j][i] == '-')
		f_tab[3] = ++i;
	if (types[j][i] == '0' && (i == 0 || !ft_isdigit(types[j][i - 1])))
		f_tab[4] = ++i;
	if (ft_isdigit(types[j][i]) && types[j][i] > '0')
	{
		if (ft_atoi(types[j] + i) > f_tab[5])
		{
			f_tab[5] = ft_atoi(types[j] + i);
			i += ft_countdigits(f_tab[5]);
		}
		else
			i++;
	}
	if (types[j][i] == '0')
		i++;
	if (f_tab[2])
		f_tab[1] = 0;
	return (i);
}

int				ft_parse_f_flags(char **types, int i, int j, int *f_tab)
{
	while (types[j][i] && \
	(ft_strchr("#0+- .", types[j][i]) || ft_isdigit(types[j][i])))
	{
		i = ft_parse_f_flags_simples(types, i, j, f_tab);
		if (types[j][i] == '.')
		{
			if (!ft_isdigit(types[j][i + 1]))
				if (ft_strchr("idDuUoOxXpsScC", types[j][++i]))
					f_tab[6] = 0;
				else
					break ;
			else if (ft_atoi(types[j] + ++i) > f_tab[6])
			{
				f_tab[6] = ft_atoi(types[j] + i);
				if (!ft_strchr("cCsS%", types[j][i + ft_countdigits(f_tab[6])])\
						&& (!f_tab[5] || f_tab[6] > f_tab[5]))
					f_tab[5] = f_tab[6];
				i += ft_countdigits(f_tab[6]);
			}
		}
	}
	return (i);
}

int				ft_parse_c_flags(char **types, int i, int j, int *f_tab)
{
	if (ft_strchr("lhjz", types[j][i]))
	{
		if (types[j][i] == 'l' && types[j][i + 1] != 'l')
			f_tab[7] = 1;
		else if (types[j][i] == 'l' && types[j][i + 1] == 'l')
		{
			f_tab[8] = 1;
			i++;
		}
		else if (types[j][i] == 'h' && types[j][i + 1] != 'h')
			f_tab[9] = 1;
		else if (types[j][i] == 'h' && types[j][i + 1] == 'h')
		{
			f_tab[10] = 1;
			i++;
		}
		else if (types[j][i] == 'j')
			f_tab[11] = 1;
		else if (types[j][i] == 'z')
			f_tab[12] = 1;
		i++;
	}
	while (types[j][i] && ft_strchr("lhjz", types[j][i]))
		i++;
	return (i);
}

static void		ft_percent(char type, int *f_tab, int *p_ret)
{
	if (!f_tab[3])
		while (f_tab[5]-- > 1)
		{
			if (f_tab[4])
				*p_ret += ft_putchar('0');
			else
				*p_ret += ft_putchar(' ');
		}
	*p_ret += ft_putchar(type);
	if (f_tab[3])
		while (f_tab[5]-- > 1)
			*p_ret += ft_putchar(' ');
}

int				ft_no_flags(char type, int *f_tab, int *p_ret)
{
	if (type == '%')
	{
		ft_percent(type, f_tab, p_ret);
		return (0);
	}
	if (!f_tab[3])
		while (--f_tab[5] > 0)
		{
			if (f_tab[4])
				*p_ret += ft_putchar('0');
			else
				*p_ret += ft_putchar(' ');
		}
	*p_ret += ft_putchar(type);
	if (f_tab[3] && !f_tab[4])
		while (--f_tab[5] > 0)
			*p_ret += ft_putchar(' ');
	return (1);
}
