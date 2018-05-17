/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 18:16:54 by pmilan            #+#    #+#             */
/*   Updated: 2018/01/08 18:54:58 by pmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf_2.h>

void	ft_precision_f(char *str, int p)
{
	int		i;

	i = 0;
	if (p == 0)
	{
		while (*str != '.')
			++str;
		*str = '\0';
		return ;
	}
	if (p == -1)
		p = 6;
	while (*str != '.')
		++str;
	++str;
	while (i < p)
		++i;
	str[i] = '\0';
}

char	*right_justify_f(char *str, int width)
{
	int		len;
	int		i;

	len = ft_strlen(str);
	if (!(str = ft_realloc(str, len + 1, width + 1)))
		return (NULL);
	ft_memmove(str + width - len, str, len + 1);
	i = -1;
	while (++i < width - len)
		str[i] = ' ';
	return (str);
}

char	*left_justify_f(char *str, int width)
{
	int		len;
	int		i;
	int		j;

	len = ft_strlen(str);
	if (!(str = ft_realloc(str, len + 1, width + 1)))
		return (NULL);
	j = -1;
	i = len;
	while (++j < width - len)
	{
		str[i] = ' ';
		++i;
	}
	str[i] = '\0';
	return (str);
}

int		ft_conv_f(char **ret, t_arg *arg)
{
	double	f;
	char	*str;

	f = (arg->arg.f > 0) ? arg->arg.f : -arg->arg.f;
	if ((str = ft_ftoa(f, arg->arg.f < 0)) == NULL)
		return (ERROR);
	if (!(str = ft_arrondis_f(str, arg->preci)))
		return (ERROR);
	ft_precision_f(str, arg->preci);
	if (ft_flags_f(&str, (arg->arg.f < 0), arg) == ERROR)
		return (ERROR);
	if (!(*ret = ft_strfreejoin(*ret, str, ft_strlen(str), arg)))
		return (ERROR);
	arg->cmpt += ft_strlen(str);
	free(str);
	return (SUCCESS);
}
