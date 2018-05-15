/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_forest.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 17:59:34 by eparisot          #+#    #+#             */
/*   Updated: 2018/01/18 13:59:15 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** f_tab[0] = '#'
** f_tab[1] = ' '
** f_tab[2] = '+'
** f_tab[3] = '-'
** f_tab[4] = '0'
** f_tab[5] = 'width'
** f_tab[6] = 'precision' (start at -1)
** f_tab[7] = 'l'
** f_tab[8] = 'll'
** f_tab[9] = 'h'
** f_tab[10] = 'hh'
** f_tab[11] = 'j'
** f_tab[12] = 'z'
*/

static int		ft_set_tabs(int *f_tab, int i, int j, char **types)
{
	f_tab[0] = 0;
	f_tab[1] = 0;
	f_tab[2] = 0;
	f_tab[3] = 0;
	f_tab[4] = 0;
	f_tab[5] = 0;
	f_tab[6] = -1;
	f_tab[7] = 0;
	f_tab[8] = 0;
	f_tab[9] = 0;
	f_tab[10] = 0;
	f_tab[11] = 0;
	f_tab[12] = 0;
	i = ft_parse_f_flags(types, i, j, f_tab);
	i = ft_parse_c_flags(types, i, j, f_tab);
	return (i);
}

int				ft_if_forest(char **types, va_list ap, int j, int *p_ret)
{
	t_tmp		*tmp;
	int			i;
	int			f_tab[13];

	i = ft_set_tabs(f_tab, 0, j, types);
	if (!ft_strchr("idDuUoOxXpsScC", types[j][i]))
		return (i + ft_no_flags(types[j][i], f_tab, p_ret));
	if ((tmp = (t_tmp *)malloc(sizeof(t_tmp))) == NULL)
		return (i);
	if (types[j][i] == 'd' || types[j][i] == 'i')
		ft_parse_di(ap, p_ret, f_tab, tmp->nbr);
	(types[j][i] == 'D') ? ft_parse_lld(ap, p_ret, f_tab, tmp->nbr) : 0;
	(types[j][i] == 'x') ? ft_parse_x(ap, p_ret, f_tab, tmp->nbr) : 0;
	(types[j][i] == 'X') ? ft_parse_llx(ap, p_ret, f_tab, tmp->nbr) : 0;
	(types[j][i] == 'o') ? ft_parse_o(ap, p_ret, f_tab, tmp->nbr) : 0;
	(types[j][i] == 'O') ? ft_parse_llo(ap, p_ret, f_tab, tmp->nbr) : 0;
	(types[j][i] == 'u') ? ft_parse_u(ap, p_ret, f_tab, tmp->nbr) : 0;
	(types[j][i] == 'U') ? ft_parse_llu(ap, p_ret, f_tab, tmp->nbr) : 0;
	(types[j][i] == 'p') ? ft_parse_p(ap, p_ret, f_tab, tmp->nbr) : 0;
	(types[j][i] == 'c') ? ft_parse_c(ap, p_ret, f_tab) : 0;
	(types[j][i] == 'C') ? ft_parse_llc(ap, p_ret, f_tab) : 0;
	(types[j][i] == 's') ? ft_parse_s(ap, p_ret, f_tab, tmp->c) : 0;
	(types[j][i] == 'S') ? ft_parse_lls(ap, p_ret, f_tab, tmp->wc) : 0;
	free(tmp);
	return (i + 1);
}
