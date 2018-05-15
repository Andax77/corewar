/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_w.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eparisot <eparisot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 20:12:08 by eparisot          #+#    #+#             */
/*   Updated: 2017/12/22 20:24:33 by eparisot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putstr_w(const wchar_t *ws, int *p_ret)
{
	int		i;

	i = 0;
	if (!ws)
	{
		ft_putstr("(null)", p_ret);
		return ;
	}
	while (ws[i])
	{
		*p_ret += ft_putchar_w(ws[i]);
		i++;
	}
}
