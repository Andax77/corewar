/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 18:43:42 by pmilan            #+#    #+#             */
/*   Updated: 2018/01/16 17:49:57 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static void		ft_skip(const char **str, int base)
{
	if (base == 16)
	{
		if (**str == '0' && ((*str)[1] == 'x' || (*str)[1] == 'X'))
			*str += 2;
	}
	else if (base == 2)
	{
		if (**str == '0' && ((*str)[1] == 'b' || (*str)[1] == 'B'))
			*str += 2;
	}
	else if (base == 8)
	{
		if (**str == '0')
			(*str)++;
	}
}

static int		ft_is_base(char c, char *eq_base, int base)
{
	int		i;

	i = -1;
	while (++i < base)
	{
		if (c == eq_base[i])
			return (i);
	}
	return (-1);
}

unsigned int	ft_atoi_base(const char *str, int base)
{
	unsigned int	nb;
	static char		eq_base[17] = "0123456789ABCDEF";

	nb = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n'
			|| *str == '\v' || *str == '\f' || *str == '\r')
		++str;
	ft_skip(&str, base);
	ft_str_toupper((char *)str);
	while (ft_is_base(*str, eq_base, base) != -1)
	{
		nb += ft_is_base(*str, eq_base, base);
		if (ft_is_base(*(++str), eq_base, base) != -1)
			nb *= base;
	}
	return (nb);
}
